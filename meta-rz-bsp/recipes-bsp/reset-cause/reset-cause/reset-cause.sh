#!/bin/bash

# Indicate the last reset cause.
# Assume WDT1 is used when issuing a software reset.

. /usr/bin/dimonoff.sh

REG_CPG_WDTOVF_RST="0x11010B10"

if [ -f /var/run/reset-cause ]; then
    reset_cause="$(cat /var/run/reset-cause)"
else
    wdtovf="$(devmem2 ${REG_CPG_WDTOVF_RST} b | grep "Read at address" | awk -F ': ' '{print $2}')"

    case "${wdtovf}" in
        0x00)
            reset_cause="por"
            ;;
        0x01|0x04)
            reset_cause="watchdog"
            ;;
        0x02|0x03|0x06)
            # 0x03|0x06 can happen if we issue a software reboot after a watchdog reboot...
            reset_cause="reboot"
            ;;
        *)
            reset_cause="unknown"
            ;;
    esac

    # Record in /var/run/reset-cause:
    echo "${reset_cause}" > /var/run/reset-cause

    # Clear WDT bits for next reset:
    devmem2 ${REG_CPG_WDTOVF_RST} w 0x00070007 1>/dev/null
fi

log_dbg "Reset cause: ${reset_cause}"

echo "${reset_cause}"
