#define OS_TASKS  5U


#define OS_ENABLE_TIMER  //использовать системный таймер для отсчёта тиков
#define OS_TIMER_SIZE 1  //размерность системного таймера (2 байта)
//#define OS_ENABLE_CRITICAL_SECTION
#define OS_PRIORITY_LEVEL    OS_PRIORITY_DISABLE

//#define OS_BSEMS      1  //количество семафоров в программе
//#define OS_ENABLE_PTIMERS
//#define OS_ENABLE_QMSG
//#define OS_ENABLE_QSMSG
//#define OS_ENABLE_CSEM
//#define OS_CSEM_SIZE    1
//#define OS_ENABLE_INT_SERVICE
//#define OS_ENABLE_ALL
