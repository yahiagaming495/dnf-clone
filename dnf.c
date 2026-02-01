#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

#define BASE_RPM_COMMAND "rpm -ivh "

void modeDownload(char *argv[]) {
  char *packagename = argv[2];
  char url[255];

  // In the fedora mirrors, There are multiple folders. Each folder has a single-letter name
  // That single-letter name represents the first letter of the packages inside it
  // The program needs to know the name of the folder the packages are in
  // So I get the first letter of the package name

  char baseurl[] = "https://mirrors.dotsrc.org/fedora-enchilada/linux/releases/42/Everything/x86_64/os/Packages/X/"; // X is the first letter of the package name
  baseurl[92] = packagename[0];
        
  CURL *curl; // Make the curl object
  CURLcode response;

  curl = curl_easy_init(); // Initalize the CURL object

  if (!curl) {
    fprintf(stderr, "curl_easy_init() failed: %s", curl_easy_strerror(response));
    exit(EXIT_FAILURE);
  }

  char rpmfilename[255] = "I";

  if (strstr(rpmfilename, ".rpm") == NULL) {
    strcat(packagename, ".rpm");
  }

  else if (strstr(rpmfilename, ".rpm")) {
    fprintf(stderr, "Please remove the .rpm extension from the command\n");
    remove(rpmfilename);
    exit(EXIT_SUCCESS);
  }

  strcpy(rpmfilename, packagename);
  snprintf(url, sizeof(url), "%s%s", baseurl, packagename);

  FILE *fp = fopen(rpmfilename, "rb");

  if (fp == NULL) {
    fp = fopen(rpmfilename, "wb");
  }
  
  else {
    char useroption[2];
    printf("The file already exists\n");
    printf("Do you want to download it again? (Y/n)\n");

    if (fgets(useroption, 2, stdin) == NULL) {
      fprintf(stderr, "Couldn't read user input");
      exit(EXIT_FAILURE);
    }

    if (strcmp(useroption, "N") == 0 || strcmp(useroption, "n") == 0) {
      exit(EXIT_SUCCESS);
    }
    
  }
  
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

  response = curl_easy_perform(curl);
  
  if (response != CURLE_OK) {
    fprintf(stderr, "The request to this URL failed: %s\n", url);
    fprintf(stderr, "%s\n", curl_easy_strerror(response));
    fclose(fp);  
    remove(rpmfilename);
    exit(EXIT_FAILURE);
  }

  int statusCode = 0;
  curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &statusCode);

    
  if (statusCode != 200) {
    fprintf(stderr, "Failed to send a request to the website: %s\n", url);
    fclose(fp);
    remove(packagename); // For some reason the rpmfilename variable was empty here, but not before a few lines (?)
    exit(EXIT_FAILURE);
  }
}

void modeInstall(char *argv[]) {
  modeDownload(argv);

  char rpm_command[255]; // Has "rpm -ivh <package-name>"
  char *packagename = argv[2];

  snprintf(rpm_command, sizeof(rpm_command), "%s%s", BASE_RPM_COMMAND, packagename);

  system(rpm_command);
  
  exit(EXIT_SUCCESS);
}

void modeSearch() { // The function will be made in a later version
  exit(EXIT_SUCCESS);
}

int handleArgs(char *argv[]) {    
  if (strcmp(argv[1], "--modes-list") == 0) {
    printf("\t\t Avaliable modes \t\t\n");
    printf("download -- Download the package without installing it\n");
    printf("install -- Download and install a package\n");
    printf("search -- Search for a package in the fedora repos\n");
    exit(EXIT_SUCCESS);
  }

  else if (strcmp(argv[1], "download") == 0) {
    modeDownload(argv);  
  }

  else if (strcmp(argv[1], "install") == 0) {
    modeInstall(argv);
  }

  else if (strcmp(argv[1], "search") == 0) {
    modeSearch();
  }

  else {
    fprintf(stderr, "Invalid mode\n");
    fprintf(stderr, "For a list full of avaliable modes, Please use the option --modes-list\n");
    exit(EXIT_FAILURE);
  }
  
  exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "USAGE: %s <mode> <name-of-package>\n", argv[0]);
    printf("Use the --modes-list option to find avaliable modes\n");
    return -1;
  }

  handleArgs(argv);
  return 0;
}
