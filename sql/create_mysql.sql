--source /home/jerry/Desktop/questionnare/sql/create_mysql.sql;
-- 使用 survey_system 数据库
USE survey_system;

-- 插入 root 用户，密码为 123456 的 MD5 加密值
INSERT INTO Users (user_name, password, is_root) VALUES ('root', MD5('123456'), 1);

-- 插入 jerry 用户，密码为 123456 的 MD5 加密值
INSERT INTO Users (user_name, password) VALUES ('jerry', MD5('123456'));

-- 创建一个问卷
INSERT INTO Surveys (title, user_id, description) VALUES ('Sample Survey', (SELECT id FROM Users WHERE user_name = 'root'), 'This is a sample survey');
INSERT INTO Surveys (title, user_id, description) VALUES ('Sample Survey', (SELECT id FROM Users WHERE user_name = 'jerry'), 'This is a sample survey');

-- 获取刚刚创建的问卷的 survey_id
SET @survey_id_root = (SELECT survey_id FROM Surveys WHERE user_id = (SELECT id FROM Users WHERE user_name = 'root') ORDER BY survey_id DESC LIMIT 1);
SET @survey_id_jerry = (SELECT survey_id FROM Surveys WHERE user_id = (SELECT id FROM Users WHERE user_name = 'jerry') ORDER BY survey_id DESC LIMIT 1);

-- 创建一个问题
INSERT INTO Questions (survey_id, question_text, question_type) VALUES (@survey_id_root, 'What is your favorite color?', 'single_choice');
INSERT INTO Questions (survey_id, question_text, question_type) VALUES (@survey_id_jerry, 'What is your favorite color?', 'single_choice');

-- 获取刚刚创建的问题的 question_id
SET @question_id_root = (SELECT question_id FROM Questions ORDER BY question_id DESC LIMIT 1);
SET @question_id_jerry = (SELECT question_id FROM Questions WHERE survey_id = @survey_id_jerry ORDER BY question_id DESC LIMIT 1);

-- 创建选项
INSERT INTO Options (question_id, option_text) VALUES (@question_id_root, 'Red');
INSERT INTO Options (question_id, option_text) VALUES (@question_id_root, 'Blue');
INSERT INTO Options (question_id, option_text) VALUES (@question_id_root, 'Green');
INSERT INTO Options (question_id, option_text) VALUES (@question_id_jerry, 'Red');
INSERT INTO Options (question_id, option_text) VALUES (@question_id_jerry, 'Blue');
INSERT INTO Options (question_id, option_text) VALUES (@question_id_jerry, 'Green');

-- 创建回答表数据（假设 root 用户回答）
INSERT INTO Responses (survey_id, question_id, user_id, answer) VALUES (@survey_id_root, @question_id_root, (SELECT id FROM Users WHERE user_name = 'root'), 'Blue');

-- 创建回答表数据（假设 jerry 用户回答）
INSERT INTO Responses (survey_id, question_id, user_id, answer) VALUES (@survey_id_jerry, @question_id_jerry, (SELECT id FROM Users WHERE user_name = 'jerry'), 'Red');