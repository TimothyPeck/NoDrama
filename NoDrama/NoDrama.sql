DROP DATABASE IF EXISTS NoDrama;
CREATE DATABASE NoDrama;

CREATE SCHEMA IF NOT EXISTS NoDrama;

SET search_path = NoDrama;

SET CLIENT_ENCODING = 'UTF-8';

DROP TABLE IF EXISTS Users CASCADE;
DROP TABLE IF EXISTS Frigo CASCADE;
DROP TABLE IF EXISTS Parties CASCADE;
DROP TABLE IF EXISTS Food CASCADE;
DROP TABLE IF EXISTS Affinities CASCADE;
DROP TABLE IF EXISTS Guests CASCADE;

CREATE TABLE Users(
    id_user SERIAL PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE, -- UNIQUE presume l'utilisation de PSQL
        email VARCHAR(255) NOT NULL UNIQUE,
        password VARCHAR(255) NOT NULL
);

CREATE TABLE Parties(
    id_party SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    date TIMESTAMP NOT NULL,
    affinity_grade int NOT NULL,
    max_people INT NOT NULL,
    host_id int NOT NULL,
    location VARCHAR(255) NOT NULL,
    FOREIGN KEY (host_id) REFERENCES Users(id_user)
);

CREATE TABLE Food(
    id_food INT NOT NULL PRIMARY KEY,
    name VARCHAR(255) NOT NULL
);

CREATE TABLE Affinities(
    fk_user1 int NOT NULL,
    fk_user2 int NOT NULL,
    affinity int NOT NULL,
    FOREIGN KEY (fk_user1) REFERENCES Users(id_user),
    FOREIGN KEY (fk_user2) REFERENCES Users(id_user),
    UNIQUE(fk_user1, fk_user2)
);

CREATE TABLE Guests(
    fk_party int NOT NULL,
    fk_user int NOT NULL,
    FOREIGN KEY (fk_party) REFERENCES Parties(id_party),
    FOREIGN KEY (fk_user) REFERENCES Users(id_user),
    UNIQUE(fk_user, fk_party)
);

CREATE TABLE Frigo(
    fk_food int NOT NULL,
    fk_party int NOT NULL,
    fk_user int NOT NULL,
    FOREIGN KEY (fk_food) REFERENCES Food(id_food),
    FOREIGN KEY (fk_party) REFERENCES Parties(id_party),
    FOREIGN KEY (fk_user) REFERENCES Users(id_user),
    UNIQUE(fk_food, fk_party, fk_user)
);
