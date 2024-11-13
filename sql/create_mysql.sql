
USE survey_system;

-- 创建一个问卷
INSERT INTO Surveys (title, user_id,) VALUES ('Sample Survey', 2);
INSERT INTO Surveys (title, user_id ) VALUES ('Sample Survey', 3);

-- 获取刚刚创建的问卷的 survey_id
SET @survey_id_tom = (SELECT survey_id FROM Surveys WHERE user_id = 3 ORDER BY survey_id DESC LIMIT 1);
SET @survey_id_jerry = (SELECT survey_id FROM Surveys WHERE user_id = 2 ORDER BY survey_id DESC LIMIT 1);

-- 创建一个问题
INSERT INTO Questions (survey_id, question_text, question_type) VALUES (@survey_id_tom, 'What is your favorite color?', 'single_choice');
INSERT INTO Questions (survey_id, question_text, question_type) VALUES (@survey_id_jerry, 'What is your favorite color?', 'single_choice');

-- 获取刚刚创建的问题的 question_id
SET @question_id_tom = (SELECT question_id FROM Questions ORDER BY question_id DESC LIMIT 1);
SET @question_id_jerry = (SELECT question_id FROM Questions WHERE survey_id = @survey_id_jerry ORDER BY question_id DESC LIMIT 1);

-- 创建选项
INSERT INTO Options (question_id, option_text) VALUES (@question_id_tom, 'Red');
INSERT INTO Options (question_id, option_text) VALUES (@question_id_tom, 'Blue');
INSERT INTO Options (question_id, option_text) VALUES (@question_id_tom, 'Green');
INSERT INTO Options (question_id, option_text) VALUES (@question_id_jerry, 'Red');
INSERT INTO Options (question_id, option_text) VALUES (@question_id_jerry, 'Blue');
INSERT INTO Options (question_id, option_text) VALUES (@question_id_jerry, 'Green');

-- 创建回答表数据（假设 tom 用户回答）
INSERT INTO Responses (survey_id, question_id, user_id, answer) VALUES (@survey_id_tom, @question_id_tom, 2, 'Blue');

-- 创建回答表数据（假设 jerry 用户回答）
INSERT INTO Responses (survey_id, question_id, user_id, answer) VALUES (@survey_id_jerry, @question_id_jerry, 3, 'Red');