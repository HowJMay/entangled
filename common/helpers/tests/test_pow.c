/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#include <unity/unity.h>

#include "common/helpers/digest.h"
#include "common/helpers/pow.h"

static tryte_t const *const TX_TRYTES = (tryte_t*)
    "XYIUIABLAEBBFCTMDCGPVNCQELHIEBVNRPWBSCABWRAVGVOVMFEHWJCUILYIXOPJNASEOHXP"
    "JBXFNHHSWEKEGEEFSAZDENWMOAXGJCQZQDGSTTMNQPYJBLRVY9T9HSQNXWYCSMLEXVWCASQ9"
    "MHPMBZ9PSSZEKCXYLDYKTOVAWQXOTGMWHUIACLUTAIKUIXZND9YMQKZBTIWOUIVQWTSBNVDC"
    "UWYP9HDMQPTXWEQYXVEOFXVGQSBHGHMKVFZZQIALVLMINZGNLEAOCQZFHPTQTQXGZQJLTBFP"
    "LWTESFYOJNJGJRYWHPEBSPSXEWCITXBJBMXDFCUDUKKGZMDOOPIBJLC9GPIBTLVQWPGTADEX"
    "NI9SWJNJXKXIJCPMICHBIFRXVWNJDP9BDELH9NOMJKGEBOCLWEXPEBFBWQLHFWQVCFIPVUXN"
    "REWXTCTFQHZYTMSUXQZTJQOWZZZCFIJ9NFXVSDFEXLODNJFREDOQ9WLLQAKRYKUCGUYEFICO"
    "LCKZHWFCLFGLKORFQFZXZXTEXWGRJPZ99KAJYFDWZNMBKQXOLRCAPDZWTZIMSUDSNDTKJLKJ"
    "WFCTHZFYFW9EF9T9OGNFBNCRDDTRQUBIBSIWJNRAFXG9UDRGSXDQ9OKAREHQOCXSULYOA9IW"
    "JOYGWYOZGVQUDNBZXHZBCCBQ9PPKIKSWLNLPRSRRYLGCQIJKYNTAJBGPAOYWIUOIR9WOQYLS"
    "QYPWKUWBD9AUVZZT9KWUNQZYLOKTWRVJDVJSDBO9XYEGJIZWRMU9SRUVGMZUX9BXACUDYNXX"
    "RTYN9UVLJUIJGNAHVWSWRFHKIXTYINVHFHGXJVVJFLFTJR9LPZCJPHQOZQRXFJPYIHCVBXCI"
    "XZFPCC9RYLOYMBXDTRDEDWPZMZYIKGTXAQYJVEFDSF9QWROXAJS9ZPAWHLKIEKUPFKXOGLUY"
    "XCQNVVBYEJG9STYYRHKAOOID9UDPCMSBOVKWXCTSRSBKOZIIUDAABKXIBIDNTXZWLITYANTG"
    "VRYBEOZAOEWGPGLKGICMPADAEHHOCUSKXBKO9REVSI9FDFDCPMUGCLJVNHMHWHAIURTWDTSH"
    "MOPVVMGWLECCPXHAAQRCDCUWDVMBRLMQYTY9PLIFIUNXZUNY9UIVHBZKMNYOPRSIKBKWDDOY"
    "JQWCSPFBLODZVAPGWHJJKOBYETEUUPJDIFLWUCMYWEUSZLWANGHYSNUXJAPFZJADQWAZCOYX"
    "WJAQCYWFBRNXJRHMIUFEROW9Z9QJAPFDIRUUTD9RPZYFD9PRPU9YVGIQMHNEYVDLEIESZEO9"
    "QLOLNHSVNGNZFHODQXXX9K9NAUDG9UENCXFTS9FQXVXJYIVBL9OPHXTPCWKEDMXXJQLXHBNT"
    "NVWHGFNNXAEKGHSBGCQFFIIRKMSYRXBCDTUCJESVXJGZTHUJWGWDD9MDXBCXEPBMDZEVUGIX"
    "HVCGDFVOYY9QEJJYQALKJWFKMYSKZRXQNGI9MC9FLSIYER9BZGDXGZUAMBZFJLWNBKMWWOSU"
    "E9XGOUPDDSCJWN9PJD9LKUVVYHCRBBBABVKZJOXFGCRXXDEGLGYDXLFFPWFNCGCRPKGSEXQN"
    "ONXKJWDGTFZWWOSK9TKUTHGHBNLQADQ9QS9XLNRVUMSRFVYVSEQEGGTOWHUMZUEVQEROFMYL"
    "XYXU9GUJSQFSMMVHQS9SVIH9X9RNORYZOLIIA9RWAUFWDKQXRAHPALEW9LDXZFSRDCPYVSSX"
    "GOEPSVZCVWXDXVJKDWUBGQEUGNAUD9GNEQEVXXLTNVBIWJLLBCTFZWODFLIIDSNUPDJRHNPH"
    "9NBOKOVXCGEEZA9ZWKRNBL9XOOPF9OCP9VORMMVSIASCEAUVVJHBLWLHDHWVJDDTEBFIKHOE"
    "VIIDJXA9MTLUSZVPJPHLRASOAGNNPQYIAZVKTROQXISIALDESIHLNREAAPXCFU9AZTORQGYC"
    "FWVFHFQMAJPUSYVAEERWGQSKYFZJPWMOAEWXTUEGIDOSSCLBFLMBIZHYIQWSCNPZUTTSKCZX"
    "DSELK9KSBHTDSUID9LMBMYXQFAWBBRHFKMMBPTFKDNLQSZAMHMYASZXXKHXKPH9TOHVZUOXD"
    "CFHBDNAQEVOQQUGKEW9YQBZWMSVTJGNVUN9TUVYJ9XECFMVIIFTNSNBCUA9TOHPHAYDSAWJT"
    "JANNPZELFSWMVLBRUKJDT9B9VWCXBMUDNLVDEEWQRITLOTFLVOUDQGEEXK9CO9DCMNDY9VZU"
    "GMLVFKLUBNSQOABRDMIWVYGMENSBHUOMGIJ9MNKLST999999999999999999999999999999"
    "999999999999999999UMJOPYD99A99999999C99999999WUIHHDPDFBHIQLKEFLUOKIOVFOC"
    "PFPWBKUCCGA9YUUEPTLUXRLZHVKEOLJQWHBOLSCWKVXCOBSVJHY9YXDMTFSSWIPNAYXJPQNQ"
    "CZAIT9ADYOLDXZVBTEUWMVYOOODSCPKAWWHOFQTLZKRPURYBMCU9YHSIYQZ9999W9VELHQPP"
    "ERYSG9ZLLAHQKDLJQBKYYZOSRQOESEELED9CZHBLAMALTJJZAFWNMWGAAUFJMNQDGKVA9999"
    "999999999999999999999999999HDU9RGVJE999999999MMMMMMMMM999999999999999999"
    "999999999";

static void test_pow(void) {
  tryte_t powed[NUM_TRYTES_SERIALIZED_TRANSACTION];
  char *nonce = iota_pow_trytes((char *)TX_TRYTES, 9);

  memcpy(powed, TX_TRYTES, NUM_TRYTES_SERIALIZED_TRANSACTION);
  memcpy(powed + NUM_TRYTES_SERIALIZED_TRANSACTION - NUM_TRYTES_NONCE, nonce, NUM_TRYTES_NONCE);

  char *hash = iota_digest((char *)powed);

  TEST_ASSERT_EQUAL_MEMORY(hash + HASH_LENGTH_TRYTE - 3, "999", 3);

  free(nonce);
  free(hash);
}

static void test_flex_pow(void) {
  flex_trit_t tx[FLEX_TRIT_SIZE_8019] = {0};
  flex_trits_from_trytes(tx, NUM_TRITS_SERIALIZED_TRANSACTION, (tryte_t *)TX_TRYTES, NUM_TRYTES_SERIALIZED_TRANSACTION,
                         NUM_TRYTES_SERIALIZED_TRANSACTION);

  flex_trit_t *nonce = iota_pow_flex(tx, FLEX_TRIT_SIZE_8019, 9);

  flex_trits_insert_from_pos(tx, NUM_TRITS_SERIALIZED_TRANSACTION, nonce, NUM_TRITS_NONCE, 0,
                             NUM_TRITS_SERIALIZED_TRANSACTION - NUM_TRITS_NONCE, NUM_TRITS_NONCE);
  flex_trit_t *fhash = iota_flex_digest(tx, FLEX_TRIT_SIZE_8019);

  tryte_t hash[NUM_TRYTES_HASH] = {0};
  flex_trits_to_trytes(hash, NUM_TRYTES_HASH, fhash, FLEX_TRIT_SIZE_243, FLEX_TRIT_SIZE_243);

  TEST_ASSERT_EQUAL_MEMORY(hash + HASH_LENGTH_TRYTE - 3, "999", 3);

  free(nonce);
  free(fhash);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_pow);
  RUN_TEST(test_flex_pow);

  return UNITY_END();
}
