--SELECT title FROM movies WHERE id IN
SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE movie_id IN
(SELECT movie_id FROM stars WHERE person_id IN 
(SELECT id FROM people WHERE name = 'Johnny Depp')) AND person_id IN
(SELECT id FROM people WHERE name = 'Helena Bonham Carter'));

--(SELECT id FROM people WHERE name = 'Johnny Depp' OR name = 'Helena Bonham Carter');