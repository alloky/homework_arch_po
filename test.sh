curl http://localhost:1234/person?login=adminadmin
curl http://localhost:1234/person?first_name=testnew&last_name=testnewlast
curl -d "login=testnew&first_name=testnewname&last_name=testnewlast&age=18"  -X POST "http://localhost:1234/person"