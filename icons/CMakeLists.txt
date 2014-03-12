FOREACH(size 16)
  FOREACH(name wait press release)
    INSTALL(FILES ${name}_${size}x${size}x32.png
      DESTINATION share/gaminggear/icons/hicolor/${size}x${size}/actions
      RENAME gaminggear-${name}.png
    )
  ENDFOREACH(name)
ENDFOREACH(size)
