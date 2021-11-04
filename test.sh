curl -d "login=testnew2&first_name=testnewname&last_name=testnewlast&age=18"  -X POST "http://localhost:1234/person";
echo "\n===============\n";
curl -X GET "http://localhost:1234/person?login=testnew2";
echo "\n===============\n";
curl -X GET "http://localhost:1234/person?first_name=testnewname&last_name=testnewlast";
echo "\n===============\n";
