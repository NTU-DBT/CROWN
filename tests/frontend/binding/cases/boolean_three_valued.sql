SELECT a.flag IS TRUE AS yes, a.flag IS NOT FALSE AS not_false, a.flag IS UNKNOWN AS unknown
FROM A AS a;
