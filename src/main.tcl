package require Tk

wm title . "PoulpeEdit : game level editor"

option add *tearOff 0

menu .menubar
. configure -menu .menubar

set m .menubar
menu $m.file
menu $m.edit
$m add cascade -menu $m.file -label File
$m add cascade -menu $m.edit -label Edit

$m.file add command -label "Close" -command "close_plp_edit"

grid [ttk::frame .c -padding "3 3 12 12"] -column 0 -row 0 -sticky nwes
grid columnconfigure . 0 -weight 1; grid rowconfigure . 0 -weight 1

set ::client_socket ""

grid [ttk::button .connect_button -text "Connect" -command "connect_to_server"] -column 0 -row 0 -sticky w
grid [ttk::button .skybox_button -text "bluesky skybox" -command "update_skybox"] -column 1 -row 0 -sticky w

proc connect_to_server {} {
  set server localhost
  set ::client_socket [socket $server 9371]
}

proc update_skybox {} {
  set sock $::client_socket
  puts $sock "updateskybox_bluesky"
  flush $sock
}

proc close_plp_edit {} {
  set sock $::client_socket
  close sock

  exit 0
}