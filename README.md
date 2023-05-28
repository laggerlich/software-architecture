# Дополнительный функционал

Глобальный администратор - пользователь, который может читать сообщения других пользователей, не входя в переписку. Если бы это реализовывалось в API

- Модерация сообщений
  - Входные данные: идентификатор сообщения
  - Выходные данные: отсутствуют

Однако администратор может поменять статус пользователя в БД на "заблокирован" и удалить сообщение из переписки.

### UPD
Реализую его... когда-нибудь :D 
Убран из линейки задач, работаю по "стандартному заданию"

### UPD2
Делаю вариант 5, а не вариант 7, поскольку я камушек и случайно взял вариант по группе, а не по потоку

* Загрузка сообщений группового чата
* Отправка P2P сообщения пользователю
* Получение P2P списка сообщений для пользователя

### Task 2

!Docker
Для запуска микросервисов в Docker, неоходимо перейти в папку [Messenger/!Docker](https://github.com/laggerlich/software-architecture/tree/main/Messenger/!Docker) и выполнить команду в консоли: 
```
docker-compose up --build
```
Тестовые данные для загрузки в базу данных находятся в [commands.sql](https://github.com/laggerlich/software-architecture/blob/main/Messenger/commands.sql).

### Task 3

Пользователи теперь хранятся в двух базах данных. Все остальные таблицы хранятся в первой базе данных.

Для загрузки тестовых данных в базу данных необходимо подключаться к ProxySQL. 

Параметры:
- DB_HOST=localhost
- DB_PORT=6033

Все таблицы базы данных для работы сервисов будут созданы при первом запуске сервисов.

* Сервис авторизации: [Messenger/UserService](https://github.com/laggerlich/software-architecture/tree/main/Messenger/UserService)
* Сервис групповых чатов: [Messenger/GroupService](https://github.com/laggerlich/software-architecture/tree/main/Messenger/GroupService)
* Сервис P2P чатов: [Messenger/P2PService](https://github.com/laggerlich/software-architecture/tree/main/Messenger/P2PService)