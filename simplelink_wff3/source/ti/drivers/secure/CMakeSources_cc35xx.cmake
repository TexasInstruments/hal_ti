cmake_minimum_required(VERSION 3.21.3)

set(SOURCES_CC35XX
    ../AESCBC.c
    ../AESCCM.c
    ../AESCMAC.c
    ../AESCTR.c
    ../AESECB.c
    ../AESGCM.c
    # ../crypto/CryptoCC32XX.c
    ../cryptoutils/cryptokey/CryptoKey.c
    ../cryptoutils/cryptokey/CryptoKeyPlaintext.c
    ../cryptoutils/hsm/HSMLPF3.c
    ../cryptoutils/hsm/HSMLPF3Utility.c
    ../cryptoutils/utils/CryptoUtils.c
    ../utils/Random.c
    ../ECDH.c
    ../ECDSA.c
    ../RNG.c
    ../SHA2.c
    ../TRNG.c
)

set(SOURCES_SEC_ONLY_CC35XX
    ${SOURCES_CC35XX}
    ../aescbc/AESCBCLPF3.c
    ../aesccm/AESCCMLPF3.c
    ../aescmac/AESCMACLPF3.c
    ../aesctr/AESCTRLPF3.c
    ../cryptoutils/ecc/ECCParamsLPF3HSM.c
    ../aesecb/AESECBLPF3.c
    ../aesgcm/AESGCMLPF3HSM.c
    ../ecdh/ECDHLPF3HSM.c
    # ../cryptoutils/aes/AESCommonWFF3.c
    ../cryptoutils/ecc/ECCParamsLPF3HSM.c
    ../cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_helpers.c
    ../cryptoutils/cryptokey/CryptoKeyKeyStore_PSA.c
    ../ecdsa/ECDSALPF3HSM.c
    # ../ecjpake/ECJPAKECC26X2.c
    # ../eddsa/EDDSACC26X2.c
    ../rng/RNGLPF3HSM.c
    ../sha2/SHA2LPF3HSM.c
    ../trng/TRNGLPF3HSM.c
)
