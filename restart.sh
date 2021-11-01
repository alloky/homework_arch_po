ssh-keygen -R "[localhost]:2222" -f /mnt/c/Users/allok/.ssh/known_hosts
docker-compose build --no-cache && docker-compose up