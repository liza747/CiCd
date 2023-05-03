#!/usr/bin/expect

spawn scp -r src/cat/s21_cat src/grep/s21_grep student@10.10.0.10:/home/student
expect {
    "yes/no" {send "yes\r";exp_continue}
    "password" {send "student\r";}
}
spawn ssh student@10.10.0.10
expect {
    "yes/no" {send "yes\r";exp_continue}
    "password" {send "student\r";}
}
expect "student" {send "sudo mv /home/student/s21_cat /home/student/s21_grep /usr/local/bin\r"}
expect {
    "password" {send "student\r";}
}
spawn ssh student@10.10.0.10
expect {
    "yes/no" {send "yes\r";exp_continue}
    "password" {send "student\r";}
}
expect "student" {send "ls /usr/local/bin\r"}
expect eof
exit