void replacePL(const char* source, char* result) {
    qq::map<const char*, const char*, 25> defines;

    // Loop through the source string
    for (size_t i = 0; i < strlen(source);) {
        // Check if this is a $define statement
        if (strncmp(&source[i], "$define ", 8) == 0) {
            const char* defineEnd = strchr(&source[i], ';');
            if (defineEnd == nullptr_) {
                return;
            }

            const char* defineStr = &source[i + 8];
            size_t defineLen = defineEnd - defineStr;
            const char* defineNameEnd = strchr(defineStr, ' ');

            if (defineNameEnd == nullptr_ || defineNameEnd - defineStr >= defineLen) {
                return;
            }

            size_t defineNameStart = &defineStr[0] - &source[0];
            size_t defineNameLen = defineNameEnd - defineStr;
            size_t defineValueStart = defineNameEnd + 1 - &source[0];
            size_t defineValueLen = defineEnd - defineNameEnd - 1;
            char text[24] = "\0";
            extractString(&source[defineNameStart], 0, ' ', text, 24);
            char val[24] = "\0";
            extractString(&source[defineValueStart], 0, ';', val, 24);
            defines[text] = val;

            i += defineEnd - &source[i] + 1;
        }
        // Check if this is an $import statement
        else if (strncmp(&source[i], "$import ", 8) == 0) {
            // Find the end of the import statement
            const char* import_end = strchr(&source[i], ';');
            if (import_end == nullptr_) {
                return;
            }

            // Get the filename and read the contents of the file
            const char* filename = &source[i + 8];
            size_t filename_len = import_end - filename;

            // Read the contents of the file
            char *contents = fread(mainFile);

            // Recursively replace any $import or $define statements in the imported file
            char replaced_contents[1024] = "\0";
            replacePL(contents, replaced_contents);
            if (replaced_contents == nullptr_) {
                return;
            }
            strcat(result, replaced_contents);

            // Move the index to the end of the import statement
            i += import_end - &source[i] + 1;
        } else {
            // Check if this is a defined value
            bool found_define = false;
            for (auto& pair : defines) {
                const char* define_n = pair.first;
                const char* define_v = pair.second;
                char txt[1024] = "\0";
                erase(&source[i], 0, 1, txt);
                bool a = strncmp(define_n, txt, strlen(define_n)) == 0 && source[i] == '$';
                if (a) {
                    strcat(result, define_v);
                    i += strlen(define_n) + 1;
                    found_define = true;
                    break;
                }
            }

            // Otherwise, just copy the current character to the result string
            if (!found_define) {
                char t = source[i];
                strncat(result, &t, 1);
                i++;
            }
        }
    }
}