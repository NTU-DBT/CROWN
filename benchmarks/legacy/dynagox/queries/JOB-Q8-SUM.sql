SELECT SUM(an.id * mc.id)
FROM AKA_NAME AS an, CAST_INFO AS ci, MOVIE_COMPANIES AS mc
WHERE an.person_id = ci.person_id AND ci.movie_id = mc.movie_id;
