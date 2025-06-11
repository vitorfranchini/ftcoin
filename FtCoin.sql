CREATE DATABASE IF NOT EXISTS ftcoin;
USE ftcoin;

CREATE TABLE IF NOT EXISTS WALLET(
    id int PRIMARY KEY AUTO_INCREMENT,
    name varchar(90),
    brokerage varchar(90)
);

CREATE TABLE IF NOT EXISTS TRANSACTION(
  id int PRIMARY KEY AUTO_INCREMENT,
  walletId int,
  operationData date,
  operationType char,
  amountMoved float(10,4) unsigned,
  FOREIGN KEY(walletId) REFERENCES WALLET(id)
);


CREATE TABLE IF NOT EXISTS ORACULO(
  date date PRIMARY KEY,
  exchange float(10,4) unsigned
);
