function getfolder()
getfolder=left(wscript.scriptfullname,instrrev(wscript.scriptfullname,"\")-1) + "\\run-win.bat"
end function

Set shell = Wscript.createobject("wscript.shell")
shell.Run  getfolder(),0