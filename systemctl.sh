#!/usr/bin/env sh

systemctl enable --now snapper-timeline.timer
systemctl enable --now snapper-cleanup.timer
systemctl enable --now kmonad
systemctl enable --now earlyoom
systemctl enable --now vnstat
