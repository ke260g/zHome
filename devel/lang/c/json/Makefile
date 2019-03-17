NAME=json_test
JSON_CFLAGS=`pkg-config --cflags json-c`
JSON_LDFLAGS=`pkg-config --libs json-c`

${NAME}: ${NAME}.c
	gcc ${JSON_CFLAGS} -o $@ $^ ${JSON_LDFLAGS}

clean:
	rm -f ${NAME}
