DROP TABLE IF EXISTS cagemenu;

CREATE TABLE cagemenu(
    fid             SMALLSERIAL PRIMARY KEY,
    category        VARCHAR NOT NULL,
    item            VARCHAR NOT NULL,
    price           VARCHAR NOT NULL,
    unique(fid, item)
);

INSERT INTO cagemenu (category, item, price) VALUES ('beverage', 'Americano', '$1.60');
INSERT INTO cagemenu (category, item, price) VALUES ('beverage','Mango Lemonade','$1.05');
INSERT INTO cagemenu (category, item, price) VALUES ('beverage','Iced Latte','$2.45');
INSERT INTO cagemenu (category, item, price) VALUES ('beverage','Strawberry Italian Soda','$2.05');
INSERT INTO cagemenu (category, item, price) VALUES ('beverage','Hot Chocolate','$2.05');
INSERT INTO cagemenu (category, item, price) VALUES ('beverage','Mango Italian Soda','$2.05');
INSERT INTO cagemenu (category, item, price) VALUES ('beverage','Chai Tea Latte','$1.05');
INSERT INTO cagemenu (category, item, price) VALUES ('beverage','Pink Lemonade','$2.90');
INSERT INTO cagemenu (category, item, price) VALUES ('beverage','Water','$0.19');
INSERT INTO cagemenu (category, item, price) VALUES ('beverage','Orange Juice','$4.00');


INSERT INTO cagemenu (category, item, price) VALUES ('food/sandwich','Grilled Cheese','$4.00');
INSERT INTO cagemenu (category, item, price) VALUES ('food/sandwich','Garlic Aioli Burger','$8.00');
INSERT INTO cagemenu (category, item, price) VALUES ('food/sandwich','St. Olaf Burger','$9.00');
INSERT INTO cagemenu (category, item, price) VALUES ('food/sandwich','Impossible Burger','$10.00');
INSERT INTO cagemenu (category, item, price) VALUES ('food/sandwich','Chicken Strips','$6.00');
INSERT INTO cagemenu (category, item, price) VALUES ('food/sandwich','Cheese Curds','$4.00');
INSERT INTO cagemenu (category, item, price) VALUES ('food/sandwich','Chicken Quesadilla','$7.00');
INSERT INTO cagemenu (category, item, price) VALUES ('food/sandwich','California Roll Sushi','$11.00');
INSERT INTO cagemenu (category, item, price) VALUES ('food/sandwich','Poki Bowl','$12.00');







