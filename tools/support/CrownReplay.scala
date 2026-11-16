import RelationType.{Attributes, Payload}
import java.io.ByteArrayOutputStream
import java.nio.charset.StandardCharsets
import java.nio.file.{Files, Paths}
import java.util.Base64
import org.apache.flink.api.common.typeinfo.{BasicTypeInfo, TypeInformation}
import org.apache.flink.api.java.functions.KeySelector
import org.apache.flink.streaming.util.ProcessFunctionTestHarnesses
import scala.collection.JavaConverters._

// Verification adapter only: feed the unchanged published process function,
// retain raw signed emissions and expose its real current-result iterator.
// G1(A,B), G2(B,C), G3(C,D) have independent set inputs; duplicates and absent
// deletes are outside this small replay's admitted operation contract.
object CrownReplay {
  def main(args: Array[String]): Unit = {
    require(args.length == 1, "expected a relation-keyed replay file")
    val function = new L3ProcessFunctions(2)
    val harness = ProcessFunctionTestHarnesses.forKeyedProcessFunction[Any, Payload, String](
      function, new KeySelector[Payload, Any] {
        override def getKey(value: Payload): Any = value._3
      }, BasicTypeInfo.INT_TYPE_INFO.asInstanceOf[TypeInformation[Any]])
    val schema = Map("G1" -> Array("A", "B"), "G2" -> Array("B", "C"), "G3" -> Array("C", "D"))
    val lines = Files.readAllLines(Paths.get(args(0)), StandardCharsets.UTF_8).asScala
    try {
      lines.zipWithIndex.foreach { case (line, index) =>
        val fields = line.split(",", -1)
        require(fields.length == 4 && Set("+", "-").contains(fields(0)) && schema.contains(fields(1)),
          "expected +/- followed by G1/G2/G3 and two int32 values")
        val values = Array[Any](fields(2).toInt, fields(3).toInt)
        val payload = Payload(if (fields(0) == "+") "Insert" else "Delete", fields(1), 0,
          Attributes(values, schema(fields(1))), (index + 1).toLong)
        val raw = new ByteArrayOutputStream()
        Console.withOut(raw) { harness.processElement(payload, (index + 1).toLong) }
        // Consume each returned Attributes immediately; do not retain a borrowed
        // joined object across iterator steps. Sorting preserves multiplicities.
        val rows = function.middle.fullAttrEnumerate(null).map { row =>
          Vector("A", "B", "C", "D").map(name => row(name).asInstanceOf[Int])
        }.toVector.sortBy(_.mkString(","))
        val jsonRows = rows.map(_.mkString("[", ",", "]")).mkString("[", ",", "]")
        val encoded = Base64.getEncoder.encodeToString(raw.toByteArray)
        println("{\"event\":" + (index + 1) + ",\"delta_base64\":\"" + encoded + "\",\"rows\":" + jsonRows + "}")
      }
    } finally harness.close()
  }
}
