hashcat_wpa2_speed=0

with open("rockyou.txt") as file:
    lines=sum(1 for _ in file)
with open("rule.rule") as rules:
    rules=sum(1 for _ in rules)

print(f"At the speed of {hashcat_wpa2_speed} hashes per second, your password would take {lines/hashcat_wpa2_speed} seconds to crack, which is {(lines/hashcat_wpa2_speed)/60} minutes and {((lines/hashcat_wpa2_speed)/60)/60}")
