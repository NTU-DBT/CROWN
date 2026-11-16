SELECT COUNT(*)
FROM PERSON_KNOWS_PERSON AS pkp1, PERSON_KNOWS_PERSON AS pkp2, PERSON_HAS_INTEREST_TAG AS phit
WHERE pkp1.person2_id = pkp2.person1_id AND pkp2.person2_id = phit.person_id;
