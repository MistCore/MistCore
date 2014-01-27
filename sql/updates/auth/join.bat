@echo off

set filename=_MERGED.sql

if exist %filename% del %filename%

:: Replace the line below with: for /r %%a in (*.sql) do (
:: to also seek out and merge .sql files in nearby, recursive directories.
for %%a in (*.sql) do (
echo -- -------------------------------------------------------- >>%filename%
echo -- %%a >>%filename%
echo -- -------------------------------------------------------- >>%filename%
copy/b %filename%+"%%a" %filename%
echo. >>%filename%
echo. >>%filename%)