# Контекст решения
<!-- Окружение системы (роли, участники, внешние системы) и связи системы с ним. Диаграмма контекста C4 и текстовое описание. 
-->
```plantuml
@startuml
!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Container.puml

Person(global_admin, "Глобальный администратор")
Person(creator, "Создатель чата")
Person(moderator, "Модератор")
Person(user, "Пользователь")


System(messenger, "Мессенджер", "Веб-приложение для ведения переписок")



Rel(global_admin, messenger, "Контроль содержимого чатов, блокировка чатов, блокировка пользователей в мессенджере")
Rel(creator, messenger, "Изменение списка участников чата, валидация и контроль публикуемого контента")
Rel(moderator, messenger, "Модерация контента и пользователей")
Rel(user, messenger, "Регистрация, просмотр/изменение информации о блогах и публикациях")



@enduml
```
## Назначение систем
|Система| Описание|
|-------|---------|
| Мессенджер | Веб-интерфейс, обеспечивающий позволяющий пользователям со всего мира общаться между собой как лично, так и посредством групповых чатов. Возможность прикреплять к сообщениям файлы, ссылки и иной контент. |
