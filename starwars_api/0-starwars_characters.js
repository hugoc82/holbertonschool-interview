#!/usr/bin/node

const request = require('request');
const movieId = process.argv[2];

if (!movieId) {
  console.error('Usage: ./0-starwars_characters.js <Movie ID>');
  process.exit(1);
}

const url = `https://swapi-api.alx-tools.com/api/films/${movieId}`;

request(url, (err, res, body) => {
  if (err) {
    console.error(err);
    return;
  }

  const movie = JSON.parse(body);
  const characters = movie.characters;

  // Appels asynchrones en série pour respecter l'ordre
  const fetchCharacter = (index) => {
    if (index >= characters.length) return;

    request(characters[index], (err, res, body) => {
      if (!err) {
        const character = JSON.parse(body);
        console.log(character.name);
        fetchCharacter(index + 1);
      }
    });
  };

  fetchCharacter(0);
});
