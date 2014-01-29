/*
 Navicat MySQL Data Transfer

 Source Server         : localhost
 Source Server Version : 50611
 Source Host           : localhost
 Source Database       : 505_world

 Target Server Version : 50611
 File Encoding         : utf-8

 Date: 05/31/2013 19:21:46 PM
*/

SET NAMES utf8;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
--  Table structure for `item_extended_cost`
-- ----------------------------
DROP TABLE IF EXISTS `item_extended_cost`;
CREATE TABLE `item_extended_cost` (
  `ID` mediumint(11) DEFAULT NULL,
  `RequiredArenaSlot` mediumint(11) DEFAULT NULL,
  `RequiredItem1` mediumint(11) DEFAULT NULL,
  `RequiredItem2` mediumint(11) DEFAULT NULL,
  `RequiredItem3` mediumint(11) DEFAULT NULL,
  `RequiredItem4` mediumint(11) DEFAULT NULL,
  `RequiredItem5` mediumint(11) DEFAULT NULL,
  `RequiredItemCount1` mediumint(11) DEFAULT NULL,
  `RequiredItemCount2` mediumint(11) DEFAULT NULL,
  `RequiredItemCount3` mediumint(11) DEFAULT NULL,
  `RequiredItemCount4` mediumint(11) DEFAULT NULL,
  `RequiredItemCount5` mediumint(11) DEFAULT NULL,
  `RequiredPersonalArenaRating` mediumint(11) DEFAULT NULL,
  `RequiredCurrency1` mediumint(11) DEFAULT NULL,
  `RequiredCurrency2` mediumint(11) DEFAULT NULL,
  `RequiredCurrency3` mediumint(11) DEFAULT NULL,
  `RequiredCurrency4` mediumint(11) DEFAULT NULL,
  `RequiredCurrency5` mediumint(11) DEFAULT NULL,
  `RequiredCurrencyCount1` mediumint(11) DEFAULT NULL,
  `RequiredCurrencyCount2` mediumint(11) DEFAULT NULL,
  `RequiredCurrencyCount3` mediumint(11) DEFAULT NULL,
  `RequiredCurrencyCount4` mediumint(11) DEFAULT NULL,
  `RequiredCurrencyCount5` mediumint(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

SET FOREIGN_KEY_CHECKS = 1;
