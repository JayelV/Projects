DROP TABLE IF EXISTS users;

CREATE TABLE users(
    uid             SMALLSERIAL PRIMARY KEY,
    username       character(10) NOT NULL,
    pin           character(4) NOT NULL,
    unique(uid, username)
);

INSERT INTO users (username, pin) VALUES ('Areeba', 1234);
INSERT INTO users (username, pin) VALUES ('Jayel', 3214);
INSERT INTO users (username, pin) VALUES ('Victoria', 9876);
INSERT INTO users (username, pin) VALUES ('Inna', 3456);