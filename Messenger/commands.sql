DELETE FROM GroupMessageRead;

DELETE FROM GroupMessage;

DELETE FROM GroupUser ;

DELETE FROM `Group`;

DELETE FROM P2P;

DELETE FROM `User`;


INSERT INTO `User`
(login, password, first_name, last_name, email)
VALUES('laggerlich', 'iLoveCoding1', 'Boris', 'Dmitrochenko', 'laggerlich@cardsec.ru');

INSERT INTO `User`
(login, password, first_name, last_name, email)
VALUES('sqwoia', 'nalilawater', 'Anastasia', 'Aksenova', 'bulo4ka@pskov.gov');

INSERT INTO `User`
(login, password, first_name, last_name, email)
VALUES('nadzor', 'iSeeU', 'Natasha', 'Aksenova', 'luki@mail.ru');

INSERT INTO `User`
(login, password, first_name, last_name, email)
VALUES('morax', 'osmanthusWine', 'Zhong', 'Li', 'liyue@teyvat.cn');

INSERT INTO `User`
(login, password, first_name, last_name, email)
VALUES('foxxy', 'birds', 'Yae', 'Miko', 'inadzuma@teyvat.cn');

INSERT INTO `User`
(login, password, first_name, last_name, email)
VALUES('bard', 'alkash', 'Venti', 'Barbatos', 'mondstat@teyvat.cn');

INSERT INTO P2P
(sender_id, receiver_id, `text`, create_date, is_read)
VALUES((select id from `User` where login = 'laggerlich'), 
	   (select id from `User` where login = 'sqwoia'), 'I love you! :3', NOW(), 0);

INSERT INTO P2P
(sender_id, receiver_id, `text`, create_date, is_read)
VALUES((select id from `User` where login = 'bard'), 
	   (select id from `User` where login = 'morax'), 'Where is my wine?!!', NOW(), 0);

INSERT INTO P2P
(sender_id, receiver_id, `text`, create_date, is_read)
VALUES((select id from `User` where login = 'sqwoia'), 
	   (select id from `User` where login = 'laggerlich'), 'You are my cutie pie <3', NOW(), 1);

INSERT INTO P2P
(sender_id, receiver_id, `text`, create_date, is_read)
VALUES((select id from `User` where login = 'foxxy'), 
	   (select id from `User` where login = 'morax'), 'Wanna hangout 2night?', NOW(), 1);

INSERT INTO P2P
(sender_id, receiver_id, `text`, create_date, is_read)
VALUES((select id from `User` where login = 'morax'), 
	   (select id from `User` where login = 'foxxy'), 'Sure. Should I take Venti with us?', NOW(), 0);



INSERT INTO `Group`
(name, author_id, create_date, able_write)
VALUES('GenshinParty', 
       (select id from `User` where login = 'morax'), NOW(), TRUE);

INSERT INTO `Group`
(name, author_id, create_date, able_write)
VALUES('WatchOut!', 
       (select id from `User` where login = 'nadzor'), NOW(), TRUE);


INSERT INTO GroupUser
(group_id, user_id, is_moder, is_admin)
VALUES((select id from `Group` where name = 'GenshinParty'), 
       (select id from `User` where login = 'bard'), 0, 0);

INSERT INTO GroupUser
(group_id, user_id, is_moder, is_admin)
VALUES((select id from `Group` where name = 'GenshinParty'), 
       (select id from `User` where login = 'foxxy'), TRUE, 0);

INSERT INTO GroupUser
(group_id, user_id, is_moder, is_admin)
VALUES((select id from `Group` where name = 'WatchOut'), 
       (select id from `User` where login = 'laggerlich'), 0, 0);

INSERT INTO GroupUser
(group_id, user_id, is_moder, is_admin)
VALUES((select id from `Group` where name = 'WatchOut'), 
       (select id from `User` where login = 'sqwoia'), 0, 0); 


INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'GenshinParty'), 
       (select id from `User` where login = 'morax'), 
       'Lets gather and kick Selecstians out!', NOW());

INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'GenshinParty'), 
       (select id from `User` where login = 'foxxy'), 
       'Did you prepared ROCKS?', NOW()); 

INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'GenshinParty'), 
       (select id from `User` where login = 'morax'), 
       'One man stone is another man gem', NOW()); 

INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'GenshinParty'), 
       (select id from `User` where login = 'bard'), 
       'My wine has been finished...', NOW()); 

INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'WatchOut'), 
       (select id from `User` where login = 'laggerlich'), 
       'nadzor, she is bullying me again!!!', NOW()); 

INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'WatchOut'), 
       (select id from `User` where login = 'nadzor'), 
       'sqwoia, is it true? Sad boy...', NOW()); 

INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'WatchOut'), 
       (select id from `User` where login = 'sqwoia'), 
       'He is lying, do not trust him!!!!', NOW()); 