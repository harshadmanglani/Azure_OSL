clear
while true
do
echo "\n\n\n1. Create student database"
echo "2. View records"
echo "3. Insert new record"
echo "4. Delete a record"
echo "5. Modify a record"
echo "6. Exit"
echo "Enter your selection: \c"
read choice
case "$choice" in
1)touch studentdb.txt
echo "Enter number of students: \c"
read numOfStudents
while [ $numOfStudents -ne 0 ]
do
echo "Enter the name of the student: \c"
read name
echo "Enter the roll number: \c"
read roll
echo "Enter the marks in Physics: \c"
read physics
echo "Enter the marks in Chemistry: \c"
read chemistry
echo "Enter the marks in Maths: \c"
read maths
average=`expr $maths + $physics + $chemistry`
average=`expr $average / 3` 
echo name:$name roll:$roll p:$physics c:$chemistry m:$maths avg:$average >> studentdb.txt
numOfStudents=`expr $numOfStudents - 1`
done
;;
2)cat studentdb.txt;;
3)echo "Enter the name of the student:\c"
read name
echo "Enter the roll number: \c"
read roll
echo "Enter the marks in Physics: \c"
read physics
echo "Enter the marks in Chemistry: \c"
read chemistry
echo "Enter the marks in Maths: \c"
read maths
average=`expr $maths + $physics + $chemistry`
average=`expr $average / 3`
echo name:$name roll:$roll p:$physics c:$chemistry m:$maths avg:$average >> studentdb.txt
;;
4)echo "Enter the roll number to delete: \c"
read delroll
grep -v "roll:$delroll" studentdb.txt >> newstudentdb.txt
rm studentdb.txt
mv newstudentdb.txt studentdb.txt
;;
5)echo "Enter the roll number you want to modify: \c"
read modroll
echo "Enter new phyiscs score: \c"
read physics
echo "Enter new chemistry score: \c"
read chemistry
echo "Enter new maths score: \c"
read maths
average=`expr $maths + $physics + $chemistry`
average=`expr $average / 3`
name=`grep "roll:$modroll" studentdb.txt|cut -d " " -f 1`
grep -v "roll:$modroll" studentdb.txt >> newstudentdb.txt
echo $name roll:$modroll p:$physics c:$chemistry m:$maths avg:$average >> newstudentdb.txt
#cat newstudentdb.txt
rm studentdb.txt
mv newstudentdb.txt studentdb.txt
echo Record modified;;
6)exit;;
*)echo "Still in development";;
esac
done



