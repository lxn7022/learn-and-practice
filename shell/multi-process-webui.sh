#!/usr/bin/env bash
#################################################
# Please do not make any changes to this file,  #
# change the variables in webui-user.sh instead #
#################################################

webui_port_first=7680
webui_port_last=7689
app_name="webui"

function checkalive_one_process()
{
    printf ">>>>>checkalive_one_process:\n"
    port=$1
    pid=`ps -ef|grep ${app_name} | grep ${port} | grep -v grep | awk '{print $2}'`
    printf "PID: ${pid} \n"
    # if not exist, return 1, then return 0
    if [ -z "${pid}" ]; then 
        printf "${app_name}:${port} is stoped\n" 
        return 1 
    else
        printf "${app_name}:${port} is running\n" 
        return 0 
    fi
}

function start_one_process()
{
    printf ">>>>>start_one_process:\n"
    port=$1
    checkalive_one_process ${port}
    if [ $? -eq "0" ]; then
        printf "${app_name}:${port} already running\n" 
    else 
        nohup ./webui.sh --port ${port} --nowebui >> ./log/webui_${port}.log 2>&1 &
        printf "${app_name}:${port} is running\n" 
    fi
}

function stop_one_process()
{
    printf ">>>>>stop_one_process:\n"
    port=$1
    checkalive_one_process ${port}
    if [ $? -eq "0" ]; then
        kill -9 ${pid}
        printf "${app_name}:${port} is stoped\n" 
    else
        printf "${app_name}:${port} already stoped\n"
    fi 
}

function status()
{
    ps -ef|grep webui | grep -v grep | grep -v multi
}

function start()
{

    for port in $(seq "${webui_port_first}" "${webui_port_last}")
    do
        start_one_process ${port}
    done
    status
}

function stop()
{
    for port in $(seq "${webui_port_first}" "${webui_port_last}")
    do
        stop_one_process ${port}
    done
    status
}


usage() 
{
    echo "Usage: $0 [start|stop|restart|status]" 
    exit 1
}

case $1 in 
    "start")
        start
        ;;
    "stop") 
        stop
        ;;
    "status")
        status
        ;;
    "restart")
        stop
        start
        ;;
    *)
        usage
        ;;
esac

