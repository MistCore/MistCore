DROP TABLE IF EXISTS `account_spell`;
CREATE TABLE `account_spell` (
  `accountId` int(11) NOT NULL,
  `spell` int(10) NOT NULL,
  `active` tinyint(1) DEFAULT NULL,
  `disabled` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`accountId`,`spell`),
  KEY `account` (`accountId`) USING HASH,
  KEY `account_spell` (`accountId`,`spell`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=latin1;