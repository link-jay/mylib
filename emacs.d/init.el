;; -*- lexical-binding: t; -*-

;; 自动配置文件
(setq custom-file "~/.emacs.d/autoinit.el")
(load-file "~/.emacs.d/autoinit.el")
(load-file "~/.emacs.d/extra.el")

;; 自动安装扩展
(require 'package)
(add-to-list 'package-archives '("melpa" . "https://melpa.org/packages/") t)
(add-to-list 'package-archives '("gnu" . "https://elpa.gnu.org/packages/") t)
(package-initialize)

(unless package-archive-contents
  (package-refresh-contents))

;; 自动安装 autoinit.el 里记录的包
(package-install-selected-packages t)

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

;; 设置字体
(set-face-attribute 'default nil
                    :family "Fira Code"
                    :height 210)
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

;; 缓冲区去除ANSI码
;; (add-hook 'compilation-filter-hook
;;           (lambda () (ansi-color-apply-on-region (point-min) (point-max))))

;; 全局快捷键
(defun my/run-compile () (interactive)
       (recompile)
       (select-window (get-buffer-window"*compilation*")))

(defun my/close-window () (interactive)
       (kill-buffer (current-buffer)))

(defun my/open-newline() (interactive)
       (move-beginning-of-line 1) (open-line 1))

(defun my/transpose-to-next-line () (interactive)
       (next-line) (transpose-lines 1) (backward-char))

(defun my/transpose-to-prev-line () (interactive)
       (next-line) (transpose-lines -1) (backward-char))

(defun my/repeat-current-line () (interactive)
  (let ((beg (line-beginning-position))
	(end (line-end-position)))
	(kill-ring-save beg end))
  (move-end-of-line 1) (newline) (yank))

(defun my/tmp-run-command (cmd)
  (interactive "scommand: ")
  (let ((ori-cmd compile-command))
    (compile cmd)
    (setq compile-command ori-cmd))
  (select-window (get-buffer-window"*compilation*")))

(global-set-key (kbd "C-h") (kbd "DEL"))
(global-set-key (kbd "C-S-h") 'help)
(global-set-key (kbd "C-z") 'universal-argument)
(global-set-key (kbd "C-u") (kbd "M-0 C-k"))
(global-set-key (kbd "C-w") (kbd "M-DEL"))
(global-set-key (kbd "C-c x") 'kill-region)
(global-set-key (kbd "C-c c") 'kill-ring-save)
(global-set-key (kbd "C-c v") 'my/repeat-current-line)
(global-set-key (kbd "<f2>") 'compile)
(global-set-key (kbd "<f5>") 'my/run-compile)
(global-set-key (kbd "S-<f2>") 'my/tmp-run-command)
(global-set-key (kbd "<f12>") 'gdb)
(global-set-key (kbd "C-<f12>") 'gdb-many-windows)
(global-set-key (kbd "M-g i") (kbd "M-x imenu RET"))
(global-set-key (kbd "C-x b") 'mode-line-other-buffer)
(global-set-key (kbd "C-x C-b") 'buffer-menu-other-window)
(global-set-key (kbd "C-x k") 'my/close-window)
(global-set-key (kbd "C-o") 'my/open-newline)
(global-set-key (kbd "M-n") 'my/transpose-to-next-line)
(global-set-key (kbd "M-p") 'my/transpose-to-prev-line)

;; 模式快捷键
(defun my/mode-open-newline () (interactive)
 (indent-for-tab-command)
 (open-newline)
 (indent-for-tab-command))

;; ===================================

(dolist (mode-hook '(c-mode-hook
		c++-mode-hook
		lua-mode-hook
		mhtml-mode-hook
		graphviz-dot-mode-hook
		zig-mode-hook))
  (add-hook mode-hook
	    (lambda () (local-set-key (kbd "C-o") 'my/mode-open-newline))))

(add-hook 'mhtml-mode-hook (lambda () (local-set-key (kbd "M-i") 'facemenu-keymap)))

(add-hook 'markdown-mode-hook
	  (lambda ()
	    (local-set-key (kbd "M-n") 'my/transpose-to-next-line)
	    (local-set-key (kbd "M-p") 'my/transpose-to-prev-line)))

;; multiple-cursors
(global-set-key (kbd "C->") 'mc/mark-next-like-this-word)
(global-set-key (kbd "C-<") 'mc/mark-previous-like-this-word)
(global-set-key (kbd "C-S-c C-S-c") 'mc/edit-lines)
(global-set-key (kbd "C-\\") 'mc/skip-to-next-like-this)
(global-set-key (kbd "C-|") 'mc/skip-to-previous-like-this)

;; yasnippet
(yas-global-mode 1)
