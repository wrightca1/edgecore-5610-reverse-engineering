set logging file /dev/shm/api_to_table_id_trace.log
set logging on
set logging overwrite on
set non-stop on
set pagination off
attach 19036
break *0x11dbdb40
commands
  info registers
  x/4x $r3
  x/4x $r4
  continue
end
break *0x11dbd3c8
commands
  info registers
  x/4x $r3
  x/4x $r4
  continue
end
break *0x11dbd3e8
commands
  info registers
  continue
end
break *0x11876f10
commands
  print/x $r4
  info registers
  bt
  continue
end
break *0x118d7ad4
commands
  print/x $r7
  bt
  continue
end
break *0x118d62ec
commands
  print/x $r7
  continue
end
break *0x1070c994
commands
  bt
  continue
end
break *0x113949c0
commands
  bt
  continue
end
continue
