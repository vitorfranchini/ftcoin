CREATE DATABASE IF NOT EXISTS ftcoin;
USE ftcoin;

CREATE TABLE IF NOT EXISTS WALLET(
	id int PRIMARY KEY AUTO_INCREMENT,
    nome varchar(90),
    corretora varchar(90)
);

CREATE TABLE IF NOT EXISTS TRANSACTION(
  id int PRIMARY KEY AUTO_INCREMENT,
  walletId int,
  dataOperacao date,
  tipoOperacao char,
  qtdMovimentado float(10,4) unsigned,
  FOREIGN KEY(walletId) REFERENCES WALLET(id)
);


CREATE TABLE IF NOT EXISTS ORACULO(
  data date PRIMARY KEY,
  cotacao float(10,4) unsigned
);
