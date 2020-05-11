SELECT title FROM(SELECT title, rating FROM ratings 
JOIN movies ON movies.id = ratings.movie_id
WHERE movie_id IN
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name = 'Chadwick Boseman')))
ORDER BY rating DESC LIMIT 5;