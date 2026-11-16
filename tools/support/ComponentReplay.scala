import RelationType.{Attributes, Payload}
import java.io.{ByteArrayOutputStream, OutputStream, PrintStream}
import java.nio.charset.StandardCharsets
import java.nio.file.{Files, Paths}
import org.apache.flink.api.common.typeinfo.{BasicTypeInfo, TypeInformation}
import org.apache.flink.api.java.functions.KeySelector
import org.apache.flink.shaded.jackson2.com.fasterxml.jackson.databind.{JsonNode, ObjectMapper}
import org.apache.flink.shaded.jackson2.com.fasterxml.jackson.databind.node.ObjectNode
import org.apache.flink.streaming.util.ProcessFunctionTestHarnesses
import scala.collection.JavaConverters._

// Optional B04 local API observer. Published classes/JARs remain unchanged.
// The qualified schedule is process plus a real full drain after EVERY event;
// its output clocks include the baseline's intrinsic Console formatting.
object ComponentReplay {
  private val mapper = new ObjectMapper()
  private case class Event(operation: String, table: String, left: Int, right: Int, phase: String)
  private def member(value: JsonNode, name: String): JsonNode = {
    val found = value.get(name)
    require(found != null, "missing component field " + name)
    found
  }
  private def text(value: JsonNode, name: String): String = {
    val found = member(value, name)
    require(found.isTextual, "expected component string " + name)
    found.textValue()
  }
  private def number(value: JsonNode, name: String, maximum: Long): Long = {
    val found = member(value, name)
    require(found.isIntegralNumber && found.canConvertToLong && found.longValue() >= 0 &&
      found.longValue() <= maximum, "invalid component integer " + name)
    found.longValue()
  }
  private def timed(target: ObjectNode, name: String, value: Long, verify: Boolean): Unit = {
    if (verify) target.putNull(name) else target.put(name, value)
  }

  // A pass keeps constant stream storage in measure mode. Verification retains
  // only a bounded current raw frame before exporting it into report memory.
  private class TextSink(capture: Boolean, maximum: Long) extends OutputStream {
    private val frame = if (capture) new ByteArrayOutputStream() else null
    var bytes = 0L
    var records = 0L
    def nextFrame(): Unit = if (capture) frame.reset()
    def captured: String = if (capture) new String(frame.toByteArray, StandardCharsets.UTF_8) else ""
    override def write(value: Int): Unit = {
      require(bytes < maximum, "component output-byte limit exceeded")
      if (capture) frame.write(value)
      bytes += 1
      if ((value & 255) == 10) records += 1
    }
    override def write(values: Array[Byte], offset: Int, count: Int): Unit = {
      require(count >= 0 && offset >= 0 && offset <= values.length-count, "invalid component stream slice")
      require(count.toLong <= maximum-bytes, "component output-byte limit exceeded")
      if (capture) frame.write(values, offset, count)
      var i = offset
      while (i < offset+count) { if (values(i) == 10) records += 1; i += 1 }
      bytes += count
    }
  }

  private def run(args: Array[String]): Int = {
    val reading = System.nanoTime()
    require(args.length == 1, "usage: ComponentReplay REQUEST.json")
    val path = Paths.get(args(0))
    require(Files.size(path) <= 64L*1024*1024, "component request exceeds 64MiB")
    val bytes = Files.readAllBytes(path)
    require(bytes.length <= 64L*1024*1024, "component request exceeds 64MiB")
    val request = mapper.readTree(bytes)
    require(number(request, "schema_version", 1) == 1, "unknown component request version")
    val command = text(request, "command")
    require(command == "verify" || command == "measure", "unknown component command")
    val verify = command == "verify"
    require(text(request, "query_family") == "l3_full_rows" &&
      text(request, "output") == "delta_and_snapshot", "unsupported fixed Scala query/output")
    val limits = member(request, "limits")
    val maximumEvents = number(limits, "input_events", 1000000)
    val maximumRecords = number(limits, "output_records", Long.MaxValue)
    val maximumBytes = number(limits, "output_bytes", Long.MaxValue)
    val warmups = number(request, "warmup_passes", 100).toInt
    val repetitions = number(request, "measured_passes", 100).toInt
    require(repetitions > 0, "component request needs a measured pass")
    val input = member(request, "events")
    require(input.isArray && input.size() <= maximumEvents, "component event limit exceeded")
    // Cold unit-set admission ends before any owner/API clock. No validation
    // set is retained during execution; the original process owns live rows.
    val events = {
      val live = scala.collection.mutable.Set.empty[(String, Int, Int)]
      input.elements().asScala.map { row =>
        val operation = text(row, "operation")
        val table = text(row, "table")
        require(Set("g1", "g2", "g3").contains(table), "unknown Scala L3 input relation")
        val values = member(row, "values")
        require(values.isArray && values.size() == 2 && values.elements().asScala.forall(v =>
          v.isIntegralNumber && v.canConvertToInt), "Scala component values must be int32 pairs")
        val key = (table, values.get(0).intValue(), values.get(1).intValue())
        if (operation == "+") require(live.add(key), "duplicate component insertion")
        else { require(operation == "-", "component operation must be + or -");
          require(live.remove(key), "absent component deletion") }
        val phase = if (row.has("phase")) text(row, "phase") else "updates"
        Event(operation, table, key._2, key._3, phase)
      }.toVector
    }
    val schema = Map("g1" -> Array("A", "B"), "g2" -> Array("B", "C"), "g3" -> Array("C", "D"))
    val names = Map("g1" -> "G1", "g2" -> "G2", "g3" -> "G3")
    val readNs = System.nanoTime()-reading
    val passes = mapper.createArrayNode()
    for (pass <- 0 until warmups+repetitions) {
      val initializing = System.nanoTime()
      val sink = new TextSink(verify, maximumBytes)
      val output = new PrintStream(sink, false, "UTF-8")
      val diagnostic = new TextSink(false, 1024*1024)
      val noise = new PrintStream(diagnostic, false, "UTF-8")
      val function = new L3ProcessFunctions(2)
      val harness = Console.withOut(noise) {
        ProcessFunctionTestHarnesses.forKeyedProcessFunction[Any, Payload, String](
          function, new KeySelector[Payload, Any] {
            override def getKey(value: Payload): Any = value._3
          }, BasicTypeInfo.INT_TYPE_INFO.asInstanceOf[TypeInformation[Any]])
      }
      val initializeNs = System.nanoTime()-initializing
      val epochs = mapper.createArrayNode()
      var snapshots = 0L
      var capturedBytes = 0L
      var loopNs = 0L
      var teardownNs = 0L
      try {
        Console.withOut(output) {
          val looping = System.nanoTime()
          events.zipWithIndex.foreach { case (event, index) =>
            sink.nextFrame()
            val previousRecords = sink.records
            val previousBytes = sink.bytes
            val transporting = System.nanoTime()
            val payload = Payload(if (event.operation == "+") "Insert" else "Delete", names(event.table), 0,
              Attributes(Array[Any](event.left, event.right), schema(event.table)), (index+1).toLong)
            val transportNs = System.nanoTime()-transporting
            val applying = System.nanoTime()
            harness.processElement(payload, (index+1).toLong)
            output.flush()
            require(!output.checkError(), "Scala component delta output failed")
            val applyNs = System.nanoTime()-applying
            val observing = System.nanoTime()
            val rows = if (verify) mapper.createArrayNode() else null
            val iterator = function.middle.fullAttrEnumerate(null)
            var emitted = 0L
            while (iterator.hasNext) {
              val row = iterator.next()
              require(snapshots < maximumRecords && sink.records <= maximumRecords-snapshots-1,
                "component output-record limit exceeded")
              snapshots += 1; emitted += 1
              if (verify) {
                val values = mapper.createArrayNode()
                Vector("A", "B", "C", "D").foreach(name => values.add(row(name).asInstanceOf[Int]))
                rows.add(values)
              }
            }
            val outputNs = System.nanoTime()-observing
            require(sink.records <= maximumRecords-snapshots, "component output-record limit exceeded")
            val actual = if (verify) mapper.createObjectNode() else null
            if (verify) {
              actual.put("delta_text", sink.captured); actual.set[JsonNode]("rows", rows)
              val size = mapper.writeValueAsBytes(actual).length.toLong
              require(size <= maximumBytes-capturedBytes, "component capture-byte limit exceeded")
              capturedBytes += size
            }
            val epoch = mapper.createObjectNode()
            epoch.put("sequence", index+1); epoch.put("phase", event.phase)
            timed(epoch, "transport_ns", transportNs, verify); timed(epoch, "apply_ns", applyNs, verify)
            timed(epoch, "output_ns", outputNs, verify); epoch.putNull("release_ns")
            epoch.put("delta_records", sink.records-previousRecords); epoch.put("snapshot_records", emitted)
            epoch.put("output_records", sink.records-previousRecords+emitted)
            epoch.put("intrinsic_text_bytes", sink.bytes-previousBytes)
            if (verify) epoch.set[JsonNode]("actual", actual) else epoch.putNull("actual")
            epochs.add(epoch)
          }
          loopNs = System.nanoTime()-looping
        }
      } finally {
        val destroying = System.nanoTime()
        // The original close footer belongs to teardown diagnostics. It is not
        // a result row, benchmark sample, or replacement for wrapper clocks.
        Console.withOut(noise) { harness.close() }
        output.close(); noise.close()
        teardownNs = System.nanoTime()-destroying
      }
      val result = mapper.createObjectNode()
      result.put("warmup", pass < warmups)
      timed(result, "initialize_ns", initializeNs, verify); timed(result, "loop_wall_ns", loopNs, verify)
      timed(result, "teardown_ns", teardownNs, verify)
      result.put("output_records", sink.records+snapshots); result.put("intrinsic_text_bytes", sink.bytes)
      if (verify) result.put("captured_result_bytes", capturedBytes) else result.putNull("captured_result_bytes")
      result.put("teardown_diagnostic_bytes", diagnostic.bytes)
      result.putNull("native_memory_before_teardown")
      result.set[JsonNode]("epochs", epochs); passes.add(result)
    }
    val report = mapper.createObjectNode()
    report.put("schema_version", 1); report.put("implementation", "legacy_scala_local_api")
    report.put("case_id", text(request,"case_id")); report.put("query_family", "l3_full_rows")
    report.put("command", command); report.put("output", "delta_and_snapshot")
    timed(report, "read_request_ns", readNs, verify); report.putNull("shared_program_ns")
    report.set[JsonNode]("passes", passes)
    report.put("scope", "local keyed-harness API observer over immutable published classes; process plus full drain every event; intrinsic delta text formatting/flush included; snapshots counted/discarded in measure; fresh logical owner per pass, JVM/JIT/allocator state may persist; no delta-only, steady-state, native-account, or pure-dispatch claim; report JSON outside service")
    System.out.println(mapper.writeValueAsString(report)); System.out.flush()
    if (System.out.checkError()) 1 else 0
  }
  def main(args: Array[String]): Unit = {
    try { if (run(args) != 0) System.exit(1) }
    catch { case error: Exception => System.err.println(error.getMessage); System.exit(1) }
  }
}
