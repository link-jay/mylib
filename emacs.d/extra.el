;; 缓冲区ANSI转义序列支持
(with-eval-after-load 'gruber-darker-theme
  (custom-set-faces
   `(ansi-color-red     ((t (:foreground "#f43841" :weight bold))))     ; ASAN 错误
   `(ansi-color-green   ((t (:foreground "#73c936"))))                  ; 成功
   `(ansi-color-yellow  ((t (:foreground "#ffdd33"))))                  ; 警告
   `(ansi-color-blue    ((t (:foreground "#96a6c8"))))			; 栈追踪(niagara)
   `(ansi-color-cyan    ((t (:foreground "#95a99f"))))                  ; quartz 偏青
   `(ansi-color-magenta ((t (:foreground "#9e95c7"))))                  ; wisteria

   `(ansi-color-bright-red   ((t (:foreground "#ff4f58" :weight bold))))
   `(ansi-color-bold         ((t (:weight bold))))))

(add-hook 'compilation-filter-hook #'ansi-color-compilation-filter)

(setq ansi-color-faces-vector
      [default
        ansi-color-red          ; 1: red → ASAN 错误
        ansi-color-green        ; 2: green
        ansi-color-yellow       ; 3: yellow/warning
        ansi-color-blue         ; 4: blue → ASAN 栈追踪
        ansi-color-magenta
        ansi-color-cyan
        default])

(setq ansi-color-names-vector nil)
