import subprocess

speed=0
rule_toggle=False

with open("rockyou.txt") as file:
    lines=sum(1 for _ in file)
with open("rule.rule") as rules:
    rules=sum(1 for _ in rules)

password_input = input("Enter Password: ")
def check_password_lists(password):
    password_check = subprocess.Popen(f"/home/sami/Desktop/C++/STEM fair/check_password {password}")

    if int(password_check ==  0):
        print(f"At the speed of {speed} hashes per second, your password would take {lines/speed} seconds to crack, which is {(lines/speed)/60} minutes and {((lines/speed)/60)/60} hours")
    elif int(password_check == 1):
        subprocess.run(f"echo {password} > temp2.txt", shell=True)
        command=subprocess.Popen("hashcat -m 99999 -a 0 temp2.txt rockyou.txt -r /Users/ellioteror/hashcat-rules/best64.rule")
        if command.returncode == 0:
            print(f"At the speed of {speed} hashes per second, your password would take {lines*rules/speed} seconds to crack using a rules-based attack, which is {(lines*rules/speed)/60} minutes and {((lines*rules/speed)/60)/60}")
        else:
            print("Your password would not be found in a dictionary or rules-based attack using our wordlist")
    elif int(password_check == 2):
        print("error in the file, recheck check_password.cpp for the right file path") 

def estimate_time(password):
    N=0
    for character in password:
        if character in "abcdefghijklmnopqrstuvwxyz":
            N = N + 26
            break
    #Let's find out if this password contains uppercase characters
    for character in password:
        if character in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
            N = N + 26
            break
    #Let's find out if this password contains number digits
    for character in password:
        if character in "0123456789":
            N = N + 10
            break
    #Let's find out if this password contains punctuation signs
    for character in password:
        if character in "!""#$%&'()*+,-./:;<=>?@[\]^_`{|}~":
            N = N + 32
            break

    L=len(password)
    combinations=N**L
    seconds = combinations/speed
    return seconds #RETURNS float/int/double

def format_time(seconds): #RETURNS STRING WATCH OUT
    if seconds < 0.001:
        return "a few milliseconds"
    if seconds < 60:
        return str(int(seconds)) + " seconds" 
    minutes = seconds / 60
    if minutes < 60:
        return str(int(minutes)) + " minutes"
    hours = minutes / 60
    if hours < 24:
        return str(int(hours)) + " hours"
    days = hours / 24
    if days < 365:
        return str(int(days)) + " days"
    months = days / 30
    if months<12:
        return str(int(months)) + " months"
    years = days / 365
    return str(int(years)) + " years"
