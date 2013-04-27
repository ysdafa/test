FILE(REMOVE_RECURSE
  "CMakeFiles/po"
  "de_DE.mo"
  "el_GR.mo"
  "en.mo"
  "es_ES.mo"
  "fr_FR.mo"
  "it_IT.mo"
  "ja_JP.mo"
  "ko_KR.mo"
  "nl_NL.mo"
  "pt_PT.mo"
  "ru_RU.mo"
  "tr_TR.mo"
  "zh_CN.mo"
  "zh_HK.mo"
  "zh_TW.mo"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/po.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
