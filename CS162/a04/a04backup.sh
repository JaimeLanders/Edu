#!/bin/bash

backupNumber=0
folderPath='./a04bu/'
fileName='a04.bu'$backupNumber'.tar'
maxNumber=10

until [ $backupNumber -ge $maxNumber ]
do
	if [ ls $folderPath | grep $fileName = $fileName
# 	ls $folderPath | grep $fileName

	((backupNumber++))
	echo backupNumber=$backupNumber

	fileName='a04.bu'$backupNumber'.tar'
	echo fileName=$fileName
done

#tar -cf $folderPath$fileName ./a04.h ./a04main.cpp ./a04implementation.cpp

#((backupNumber++))
#echo backupNumber=$backupNumber
