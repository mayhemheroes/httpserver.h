#include "munit.h"
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "parser.h"

void setup_buffer_and_parser(struct hsh_parser_s *parser,
                             struct hsh_buffer_s *buffer, char const *req_str, int size) {
  // setup parser
  hsh_parser_init(parser);

  // setup input buffer
  int len = strlen(req_str);
  buffer->buf = malloc(size);
  buffer->capacity = size;
  memcpy(buffer->buf, req_str, len);
  buffer->length = len;
  buffer->sequence_id = 1;
}

//MunitResult test_parser_small_body_complete(const MunitParameter params[], void *data) {
//int main(int argc, char *argv[]) {
int LLVMFuzzerTestOneInput(char* data, size_t size) {
    
    
  /*(void)params;
  (void)data;*/
  char const *request_string =
      "GET /foo HTTP/1.1\r\nHost: www.jeremycw.com\r\nContent-Length: "
      "16\r\n\r\naaaaaaaaaaaaaaaa";

  struct hsh_parser_s parser = {0};
  struct hsh_buffer_s buffer = {0};
  //setup_buffer_and_parser(&parser, &buffer, request_string);
  setup_buffer_and_parser(&parser, &buffer, data, size);

  enum hsh_token_e expected_types[] = {
      HSH_TOK_METHOD,       HSH_TOK_TARGET,       HSH_TOK_VERSION,
      HSH_TOK_HEADER_KEY,   HSH_TOK_HEADER_VALUE, HSH_TOK_HEADER_KEY,
      HSH_TOK_HEADER_VALUE, HSH_TOK_HEADERS_DONE, HSH_TOK_BODY};

  char const *expected_values[] = {"GET",
                                   "/foo",
                                   "HTTP/1.1",
                                   "Host",
                                   "www.jeremycw.com",
                                   "Content-Length",
                                   "16",
                                   "",
                                   "aaaaaaaaaaaaaaaa"};

  int i = 0;
  struct hsh_token_s out;
  out = hsh_parser_exec(&parser, &buffer, size);
  /*while ((out = hsh_parser_exec(&parser, &buffer, size)).type != HSH_TOK_NONE) {
    munit_assert_memory_equal(out.len, expected_values[i],
                              &buffer.buf[out.index]);
    munit_assert(expected_types[i] == out.type);
    if (out.type == HSH_TOK_HEADERS_DONE) {
      munit_assert(out.flags == 0);
    }
    i++;
  }*/

  //munit_assert(i == 9);

  free(buffer.buf);

  //return MUNIT_OK;
  return 0;
}
