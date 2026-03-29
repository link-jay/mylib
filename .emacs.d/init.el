;; 自动配置文件
(setq custom-file "~/.emacs.d/autoinit.el")
(load-file "~/.emacs.d/autoinit.el")

;; 关闭保存的一些设置
(setq make-backup-files nil
      auto-save-default nil
      create-lockfiles nil)

;; 去除bar栏,menu栏,滑动栏,标题栏
(tool-bar-mode -1)
(menu-bar-mode -1)
(scroll-bar-mode -1)
(add-to-list 'default-frame-alist '(undecorated . t))

;; 关闭启动页
(setq inhibit-startup-screen t)

;; 设置背景透明
(set-frame-parameter nil 'alpha-background 80)

;; 设置行号
(global-display-line-numbers-mode 1)

;; 设置字号字体
(add-to-list 'default-frame-alist '(font . "FiraCode-21"))

;; 改光标
(setq-default cursor-type 'bar)

;; 翻页
;;(setq next-screen-context-lines 13)

;; 补全
(electric-pair-mode 1)

;; gdb模式增强
(setq gdb-many-windows t)

;; 追踪链接
(setq find-file-visit-truename t)

;; 全局快捷键
(global-set-key (kbd "C-h") (kbd "DEL"))
(global-set-key (kbd "C-S-h") 'help)
(global-set-key (kbd "C-z") 'universal-argument)
(global-set-key (kbd "C-u") (kbd "M-0 C-k"))
(global-set-key (kbd "C-w") (kbd "M-DEL"))
(global-set-key (kbd "C-c x") 'kill-region)
(global-set-key (kbd "C-c c") 'kill-ring-save)
(global-set-key (kbd "<f5>") (kbd "M-x compile"))
(global-set-key (kbd "C-x b") 'mode-line-other-buffer)
(global-set-key (kbd "C-x C-b") 'buffer-menu-other-window)
(global-set-key (kbd "C-x k") (lambda () (interactive) (kill-buffer (current-buffer))))
(global-set-key (kbd "C-o") (lambda () (interactive) (move-beginning-of-line 1) (open-line 1)))
(global-set-key (kbd "M-o")  (lambda () (interactive) (move-end-of-line 1) (newline 1)))
(global-set-key (kbd "M-n") (lambda () (interactive) (next-line) (transpose-lines 1) (backward-char)))
(global-set-key (kbd "M-p") (lambda () (interactive) (next-line) (transpose-lines -1) (backward-char)))

;; 模式快捷键
(dolist (hook '(c-mode-hook lua-mode-hook mhtml-mode-hook))
  (add-hook hook
	    (lambda ()
	      (local-set-key (kbd "C-o") (kbd "C-a RET C-p TAB"))
	      (local-set-key (kbd "M-o") (kbd "C-e RET TAB")))))

(add-hook 'mhtml-mode-hook
	  (lambda ()
	    (local-set-key (kbd "M-i") 'facemenu-keymap)))

(add-hook 'markdown-mode-hook
	  (lambda ()
	    (local-set-key (kbd "M-n")
			   (lambda () (interactive) (next-line) (transpose-lines 1) (backward-char)))
	    (local-set-key (kbd "M-p")
			   (lambda () (interactive) (next-line) (transpose-lines -1) (backward-char)))))

;; multiple-cursors
(global-set-key (kbd "C->") 'mc/mark-next-like-this-word)
(global-set-key (kbd "C-<") 'mc/mark-previous-like-this-word)
(global-set-key (kbd "C-S-c C-S-c") 'mc/edit-lines)
(global-set-key (kbd "C-\\") 'mc/skip-to-next-like-this)
(global-set-key (kbd "C-|") 'mc/skip-to-previous-like-this)

;; yasnippet
(yas-global-mode 1)
