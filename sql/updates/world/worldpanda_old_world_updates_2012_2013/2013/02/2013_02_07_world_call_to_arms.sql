/*
SQLyog Ultimate v9.02 
MySQL - 5.5.28-29.2-log 
*********************************************************************
*/
/*!40101 SET NAMES utf8 */;

DROP TABLE `game_event_battleground_holiday`; 

delete from game_event where coment like "%Call to Arms:%";
insert into `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) values('19','2013-01-06 08:00:00','2020-12-31 06:00:00','90720','10080','284','Call to Arms: Warsong Gulch!','0');
insert into `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) values('53','2013-01-13 08:00:00','2020-12-31 06:00:00','90720','10080','400','Call to Arms: Strand of the Ancients!','0');
insert into `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) values('54','2013-01-20 08:00:00','2020-12-31 06:00:00','90720','10080','420','Call to Arms: Isle of Conquest!','0');
insert into `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) values('20','2013-01-27 08:00:00','2020-12-31 06:00:00','90720','10080','285','Call to Arms: Arathi Basin!','0');
insert into `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) values('21','2013-02-03 08:00:00','2020-12-31 06:00:00','90720','10080','353','Call to Arms: Eye of the Storm!','0');
insert into `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) values('18','2013-02-10 08:00:00','2020-12-31 06:00:00','90720','10080','283','Call to Arms: Alterac Valley!','0');
insert into `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) values('65','2013-02-17 08:00:00','2020-12-31 06:00:00','90720','10080','435','Call to Arms: Battle for Gilneas','0');
insert into `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) values('66','2013-02-24 08:00:00','2020-12-31 06:00:00','90720','10080','436','Call to Arms: Twin Peaks','0');
insert into `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) values('67','2013-03-03 08:00:00','2020-12-31 06:00:00','90720','10080','488','Call to Arms: Silvershard Mines','0');
insert into `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) values('68','2013-03-10 08:00:00','2020-12-31 06:00:00','90720','10080','489','Call to Arms: Temple of Kotmogu','0');
