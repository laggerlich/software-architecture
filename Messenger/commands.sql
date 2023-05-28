DELETE FROM GroupMessageRead;

DELETE FROM GroupMessage;

DELETE FROM GroupUser ;

DELETE FROM `Group`;

DELETE FROM P2P;

DELETE FROM `User` -- sharding:0
;

DELETE FROM `User` -- sharding:1
;

INSERT INTO `User`
(id, login, password, first_name, last_name, email)
VALUES(1, 'laggerlich', 'iLoveCoding1', 'Boris', 'Dmitrochenko', 'laggerlich@cardsec.ru'); -- sharding:0
;

INSERT INTO `User`
(id, login, password, first_name, last_name, email)
VALUES(2, 'sqwoia', 'nalilawater', 'Anastasia', 'Aksenova', 'bulo4ka@pskov.gov'); -- sharding:1
;

INSERT INTO `User`
(id, login, password, first_name, last_name, email)
VALUES(3, 'nadzor', 'iSeeU', 'Natasha', 'Aksenova', 'luki@mail.ru'); -- sharding:0
;

INSERT INTO `User`
(id, login, password, first_name, last_name, email)
VALUES(4, 'morax', 'osmanthusWine', 'Zhong', 'Li', 'liyue@teyvat.cn'); -- sharding:1
;

INSERT INTO `User`
(id, login, password, first_name, last_name, email)
VALUES(5, 'foxxy', 'birds', 'Yae', 'Miko', 'inadzuma@teyvat.cn'); -- sharding:0
;

INSERT INTO `User`
(id, login, password, first_name, last_name, email)
VALUES(6, 'bard', 'alkash', 'Venti', 'Barbatos', 'mondstat@teyvat.cn'); -- sharding:1
;

INSERT INTO P2P
(sender_id, receiver_id, `text`, create_date, is_read)
VALUES(1, 2, 'I love you! :3', NOW(), 0);

INSERT INTO P2P
(sender_id, receiver_id, `text`, create_date, is_read)
VALUES(6, 4, 'Where is my wine?!!', NOW(), 0);

INSERT INTO P2P
(sender_id, receiver_id, `text`, create_date, is_read)
VALUES(2, 1, 'You are my cutie pie <3', NOW(), 1);

INSERT INTO P2P
(sender_id, receiver_id, `text`, create_date, is_read)
VALUES(5, 4, 'Wanna hangout 2night?', NOW(), 1);

INSERT INTO P2P
(sender_id, receiver_id, `text`, create_date, is_read)
VALUES(4, 5, 'Sure. Should I take Venti with us?', NOW(), 0);



INSERT INTO `Group`
(name, author_id, create_date, able_write)
VALUES('GenshinParty', 4, NOW(), TRUE);

INSERT INTO `Group`
(name, author_id, create_date, able_write)
VALUES('WatchOut!', 3, NOW(), TRUE);


INSERT INTO GroupUser
(group_id, user_id, is_moder, is_admin)
VALUES((select id from `Group` where name = 'GenshinParty'), 6, 0, 0);

INSERT INTO GroupUser
(group_id, user_id, is_moder, is_admin)
VALUES((select id from `Group` where name = 'GenshinParty'), 5, TRUE, 0);

INSERT INTO GroupUser
(group_id, user_id, is_moder, is_admin)
VALUES((select id from `Group` where name = 'WatchOut'), 1, 0, 0);

INSERT INTO GroupUser
(group_id, user_id, is_moder, is_admin)
VALUES((select id from `Group` where name = 'WatchOut'), 2, 0, 0); 


INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'GenshinParty'), 4, 'Lets gather and kick Selecstians out!', NOW());

INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'GenshinParty'), 5, 'Did you prepared ROCKS?', NOW()); 

INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'GenshinParty'), 4, 'One man stone is another man gem', NOW()); 

INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'GenshinParty'), 6, 'My wine has been finished...', NOW()); 

INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'WatchOut'), 1, 'nadzor, she is bullying me again!!!', NOW()); 

INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'WatchOut'), 3, 'sqwoia, is it true? Sad boy...', NOW()); 

INSERT INTO GroupMessage
(group_id, sender_id, `text`, create_date)
VALUES((select id from `Group` where name = 'WatchOut'), 2, 'He is lying, do not trust him!!!!', NOW()); 