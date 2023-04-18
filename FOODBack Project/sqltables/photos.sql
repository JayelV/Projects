DROP TABLE IF EXISTS photos;

CREATE TABLE photos(
    pid             SMALLSERIAL PRIMARY KEY,
    uid             int references users(uid),
    date            DATE DEFAULT CURRENT_DATE,
    url             VARCHAR NOT NULL,
    unique(uid, url)
);

INSERT INTO photos (uid, url) VALUES (1, 'https://i.imgur.com/4021Epi.jpg');
INSERT INTO photos (uid, url) VALUES (1, 'https://i.imgur.com/hcoLG5k.jpg');
INSERT INTO photos (uid, url) VALUES (3, 'https://i.imgur.com/4021Epi.jpg');
INSERT INTO photos (uid, url) VALUES (4, 'https://i.imgur.com/2jEkk7i.jpg');
