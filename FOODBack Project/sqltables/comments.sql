DROP TABLE IF EXISTS comments;

CREATE TABLE comments(
    cid             SMALLSERIAL PRIMARY KEY,
    uid             int references users(uid),
    date            DATE DEFAULT CURRENT_DATE,

    neg_feedback    VARCHAR NOT NULL,
    comment         VARCHAR NOT NULL,
    votes           int NOT NULL DEFAULT 0,
    -- votes           VARCHAR NOT NULL DEFAULT "0",    

    unique(comment)
);

-- INSERT INTO comments (uid, comment, votes) VALUES (3, 'Tomato basil soup please!', 5);
-- INSERT INTO comments (uid, comment, votes) VALUES (2,'Where is the sriracha??', 3);
-- INSERT INTO comments (uid, comment, votes) VALUES (1,'lines are ridiculos. need another caf', 2);
-- INSERT INTO comments (uid, comment, votes) VALUES (4,'More normal soup options please.', -6);

-- SELECT * FROM comment ORDER BY votes asc; -- ascending order
-- SELECT * FROM comment ORDER BY votes desc; -- descending order
