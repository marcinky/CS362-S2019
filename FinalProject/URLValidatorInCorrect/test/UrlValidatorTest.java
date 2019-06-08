/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import junit.framework.TestCase;
import java.util.Random;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision$
 */
public class UrlValidatorTest extends TestCase {

 HEAD
    public void testLocal(){
        UrlValidator url = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
        assertTrue(url.isValid("http://localhost/local/local.txt"));
        assertTrue(url.isValid("http://fakelocal/fake/fake.csv"));
        assertTrue(url.isValid("http://localhost"));
        assertTrue(url.isValid("http://fakehost"));
    }

    public void testPortNums(){
        UrlValidator url = new UrlValidator();
        assertTrue(url.isValid("http://apple.com:0/path"));
        assertTrue(url.isValid("http://apple.com:1/path"));
        assertTrue(url.isValid("http://apple.com:20000/path"));
        assertTrue(url.isValid("http://apple.com:65535/path"));
        assertFalse(url.isValid("http://apple.com:65536/path"));
        assertFalse(url.isValid("http://apple.com:-1/path"));
        assertFalse(url.isValid("http://apple.com:-20000/path"));
        assertFalse(url.isValid("http://apple.com:-65535/path"));
	assertFalse(url.isValid("http://apple.com:-99999/path"));
	assertFalse(url.isValid("http://apple.com:99999/path"));
    }
	
	public void testScheme(){
		UrlValidator url = new UrlValidator();
		assertTrue(url.isValid("http://apple.com:0/path"));
		assertTrue(url.isValid("ftp://apple.com:0/path"));
		assertTrue(url.isValid("h3t://apple.com:0/path"));
		assertFalse(url.isValid("3ht://apple.com:0/path"));
		assertFalse(url.isValid("http:/apple.com:0/path"));
		assertFalse(url.isValid("http:apple.com:0/path"));
		assertFalse(url.isValid("http/apple.com:0/path"));
		assertFalse(url.isValid("://apple.com:0/path"));
		assertFalse(url.isValid("apple.com:0/path"));
		assertFalse(url.isValid("htp://apple.com:0/path"));
		assertFalse(url.isValid("thtp://apple.com:0/path"));
	}
	
	public void testAuthority(){
		UrlValidator url = new UrlValidator();
		assertTrue(url.isValid("http://apple.com:0/path"));
		assertTrue(url.isValid("http://ap.com:0/path"));
		assertTrue(url.isValid("http://apple.ca:0/path"));
		assertTrue(url.isValid("http://0.0.0.0:0/path"));
		assertTrue(url.isValid("http://255.255.255.255:0/path"));
		assertTrue(url.isValid("http://256.com:0/path"));
		assertTrue(url.isValid("http://ap.cc:0/path"));
		assertFalse(url.isValid("http://256.256.256.256:0/path"));
		assertFalse(url.isValid("http://256.0.0.0:0/path"));
		assertFalse(url.isValid("http://0.0.0.0.0:0/path"));
		assertFalse(url.isValid("http://0.0.0.0.:0/path"));
		assertFalse(url.isValid("http://0.0.0:0/path"));
		assertFalse(url.isValid("http://.0.0.0.0:0/path"));
		assertFalse(url.isValid("http://apple.c:0/path"));
		assertFalse(url.isValid("http://apple.ala:0/path"));
		assertFalse(url.isValid("http://apple.laa:0/path"));
		assertFalse(url.isValid("http://apple.:0/path"));
		assertFalse(url.isValid("http://.apple:0/path"));
		assertFalse(url.isValid("http://apple:0/path"));
		assertFalse(url.isValid("http://:0/path"));
	}
	
	public void testPath(){
		UrlValidator url = new UrlValidator();
		assertTrue(url.isValid("http://apple.com:0/path"));
		assertTrue(url.isValid("http://apple.com:0/t123"));
		assertTrue(url.isValid("http://apple.com:0/$23"));
		assertTrue(url.isValid("http://apple.com:0//path/"));
		assertTrue(url.isValid("http://apple.com:0"));
		assertTrue(url.isValid("http://apple.com:0/path/file"));
		assertFalse(url.isValid("http://apple.com:0/.."));
		assertFalse(url.isValid("http://apple.com:0/../"));
		assertFalse(url.isValid("http://apple.com:0/../file"));
		assertFalse(url.isValid("http://apple.com:0/..//file"));
		assertFalse(url.isValid("http://apple.com:0/path//file"));
	}
	
	public void testQuery(){
		UrlValidator url = new UrlValidator();
		assertTrue(url.isValid("http://apple.com:0/path?action=view"));
		assertTrue(url.isValid("http://apple.com:0/path?action=edit&mode=up"));
		assertTrue(url.isValid("http://apple.com:0/path"));
		assertFalse(url.isValid("http://apple.com:0/path?atcion=view"));
	}

    public static ResultPair[][] getURL() {
        ResultPair[] testUrlScheme = {new ResultPair("http:/", false),
                new ResultPair("ftp:/", false),
                new ResultPair("https:/", false),
                new ResultPair("gopher:/", false),
                new ResultPair("telnet:/", false),
                new ResultPair("http://", true),
                new ResultPair("ftp://", true),
                new ResultPair("https://", true),
                new ResultPair("gopher://", true),
                new ResultPair("telnet://", true),
                new ResultPair("http;/", false),
                new ResultPair("http;//", false),
                new ResultPair("http//:", false),
                new ResultPair("ftp;/", false),
                new ResultPair("ftp;//", false),
                new ResultPair("ftp//:", false),
                new ResultPair("https;/", false),
                new ResultPair("https;//", false),
                new ResultPair("https//:", false),
                new ResultPair("gopher;/", false),
                new ResultPair("gopher;//", false),
                new ResultPair("gopher//:", false),
                new ResultPair("telnet;/", false),
                new ResultPair("telnet;//", false),
                new ResultPair("telnet//:", false)};
        ResultPair[] testUrlAuthority = {new ResultPair("-www.cat.com", false),
                new ResultPair("www.cat.com-", false),
                new ResultPair("-www.cat.com-", false),
                new ResultPair("www.cat.com.@", false),
                new ResultPair("www.c^^t.com", false),
                new ResultPair("www.c@t.com-", false),
                new ResultPair("www.cat.com", true),
                new ResultPair("en.cat.com", true),
                new ResultPair("cat.com", true),
                new ResultPair("www.cat.org-", false),
                new ResultPair("-www.cat.com", false),
                new ResultPair("www.dog.com-", false),
                new ResultPair("-www.dog.com-", false),
                new ResultPair("www.dog.com.@", false),
                new ResultPair("www.c^^t.com", false),
                new ResultPair("www.c@t.com-", false),
                new ResultPair("www.dog.com", true),
                new ResultPair("en.dog.com", true),
                new ResultPair("dog.com", true),
                new ResultPair("www.dog.org-", false)};
        ResultPair[] testUrlPort = {new ResultPair(":200", true),
                new ResultPair(":0", true), // max possible
                new ResultPair(":1000000", false), // max possible +1
                new ResultPair(":1", true),
                new ResultPair("", true),
                new ResultPair(":asd", false),
                new ResultPair(":65asd65", false),
                new ResultPair(":asd65", false),
                new ResultPair(":65asd", false)};
        ResultPair[] testPath = {new ResultPair("/apple", true),
                new ResultPair("/apple1", true),
                new ResultPair("/1apple", true),
                new ResultPair("...", false),
                new ResultPair(".../", false)};
        ResultPair[] testUrlQuery = {new ResultPair("/apple", true),
                new ResultPair("?awesome=10", true),
                new ResultPair("?great=yes&cool=no", true)};
        ResultPair[][] allOptions = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
        return allOptions;
    }

    /*
    public void randomTests() {
        ResultPair[][] allOptions = getURL();
        System.out.println("Test Print " + allOptions[0][1].item);
        int x = 5;
        int y = 4;
        assertTrue(x > y);
        System.out.println(allOptions[0].length);
    }
     */

    public void testRandomly() {
        ResultPair[][] allOptions = getURL();
        int schemesLength = allOptions[0].length;
        int authoritiesLength = allOptions[1].length;
        int portsLength = allOptions[2].length;
        int pathsLength = allOptions[3].length;
        int queriesLength = allOptions[4].length;

        for (int i = 0; i < 100000; i++){
            ResultPair scheme = allOptions[0][new Random().nextInt(schemesLength)];
            ResultPair authority = allOptions[1][new Random().nextInt(authoritiesLength)];
            ResultPair port = allOptions[2][new Random().nextInt(portsLength)];
            ResultPair path = allOptions[3][new Random().nextInt(pathsLength)];
            ResultPair query = allOptions[4][new Random().nextInt(queriesLength)];

            boolean x = true;

            if(scheme.valid == false){
                x = false;
            } else if(authority.valid == false){
                x = false;
            } else if(port.valid == false){
                x = false;
            } else if(path.valid == false){
                x = false;
            } else if(query.valid == false){
                x = false;
            }


            String url = "";
            url = url.concat(scheme.item).concat(authority.item).concat(port.item).concat(path.item).concat(query.item);
            //System.out.println(url);
            //System.out.println(x);

            UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
            if(x == true){
                assertTrue(urlVal.isValid(url));
            } else if(x == false){
                assertFalse(urlVal.isValid(url));
            }
        }

    }

 ProjectPartB-RandomTests

}
