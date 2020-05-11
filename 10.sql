SELECT COUNT(name) FROM people WHERE id IN 
(SELECT person_id FROM directors WHERE movie_id IN
(SELECT  movie_id FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE rating >= 9));

