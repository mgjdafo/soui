#pragma once

//����һ��SOUI�ڲ�ʹ�õ�LOG����꣬"soui"����LOG ID��"soui-lib"���ڶ���log��filter.
//�û���Ҫʹ��LOG���Է����������ʽ���壬��������APP��ֱ��ʹ������ĺꡣ

#define SLOG_TRACE( log) LOG_TRACE("soui", "soui-lib", log) 
#define SLOG_DEBUG( log) LOG_DEBUG("soui", "soui-lib", log) 
#define SLOG_INFO ( log) LOG_INFO ("soui", "soui-lib", log)  
#define SLOG_WARN ( log) LOG_WARN ("soui", "soui-lib", log)  
#define SLOG_ERROR( log) LOG_ERROR("soui", "soui-lib", log) 
#define SLOG_ALARM( log) LOG_ALARM("soui", "soui-lib", log) 
#define SLOG_FATAL( log) LOG_FATAL("soui", "soui-lib", log) 


#define SLOGFMTT( fmt, ...) LOGFMT_TRACE("soui", "soui-lib", fmt,  ##__VA_ARGS__)
#define SLOGFMTD( fmt, ...) LOGFMT_DEBUG("soui", "soui-lib", fmt,  ##__VA_ARGS__)
#define SLOGFMTI( fmt, ...) LOGFMT_INFO("soui", "soui-lib", fmt,  ##__VA_ARGS__)
#define SLOGFMTW( fmt, ...) LOGFMT_WARN("soui", "soui-lib", fmt,  ##__VA_ARGS__)
#define SLOGFMTE( fmt, ...) LOGFMT_ERROR("soui", "soui-lib", fmt,  ##__VA_ARGS__)
#define SLOGFMTA( fmt, ...) LOGFMT_ALARM("soui", "soui-lib", fmt,  ##__VA_ARGS__)
#define SLOGFMTF( fmt, ...) LOGFMT_FATAL("soui", "soui-lib", fmt,  ##__VA_ARGS__)
