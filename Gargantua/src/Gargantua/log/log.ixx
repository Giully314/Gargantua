/*
* gargantua/log/log.ixx
* 
* This module defines easy access to logging inside the project. Logging can be customized by creating a 
* custom stream type and pass it to the Logger.
*/
export module gargantua.log.log;

export import gargantua.log.logger;
export import gargantua.log.console_stream;
export import gargantua.log.mutex_console_stream;
export import gargantua.log.logger_system;