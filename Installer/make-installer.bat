#this is currently only git bash compatible but that's all I use

rm -r package; mkdir package; mkdir package/Bin32; mkdir package/Dependencies

cp ../Bin32/CrysisVR.dll package/Bin32
cp ../Dependencies/*.dll package/Dependencies
cp ../*.* package/

/c/Program\ Files\ \(x86\)/NSIS/makensis.exe installer.nsi