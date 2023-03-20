#pragma once

#ifndef GRG_LOGGER_ON
#define GRG_LOGGER_ON
#endif

#ifdef GRG_LOGGER_ON
#define GRG_CORE_DEBUG(...)				::gargantua::log::LoggerSystem::GetEngineLogger().Debug(__VA_ARGS__)
#define GRG_CORE_INFO(...)				::gargantua::log::LoggerSystem::GetEngineLogger().Info(__VA_ARGS__)
#define GRG_CORE_WARNING(...)			::gargantua::log::LoggerSystem::GetEngineLogger().Warning(__VA_ARGS__)
#define GRG_CORE_ERROR(...)				::gargantua::log::LoggerSystem::GetEngineLogger().Error(__VA_ARGS__)
#define GRG_CORE_LOGGER_FILTER(x)		::gargantua::log::LoggerSystem::GetEngineLogger().SetLevel(x)

#else
#define GRG_CORE_DEBUG(...)		
#define GRG_CORE_INFO(...)		
#define GRG_CORE_WARNING(...)	
#define GRG_CORE_ERROR(...)		
#define GRG_CORE_LOGGER_FILTER(x)
#endif