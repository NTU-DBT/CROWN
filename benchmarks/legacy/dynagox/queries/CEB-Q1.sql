SELECT COUNT(*)
FROM CAST_INFO AS ci, MOVIE_INFO AS mi, PERSON_INFO AS pi
WHERE pi.person_id = ci.person_id AND ci.movie_id = mi.movie_id;
