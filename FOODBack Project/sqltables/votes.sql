DROP TABLE IF EXISTS votes;

CREATE TABLE votes(
    vid             SMALLSERIAL PRIMARY KEY,
    cid             VARCHAR NOT NULL,
    uid             VARCHAR NOT NULL,

    response        VARCHAR NOT NULL,
    unique(cid, uid)
);
