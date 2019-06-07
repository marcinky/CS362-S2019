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

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision$
 */
public class UrlValidatorTest extends TestCase {

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

}
